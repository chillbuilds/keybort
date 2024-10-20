
window.addEventListener('DOMContentLoaded', () => {
  const replaceText = (selector, text) => {
    const element = document.getElementById(selector)
    if (element) element.innerText = text
  }

  for (const type of ['chrome', 'node', 'electron']) {
    replaceText(`${type}-version`, process.versions[type])
  }
})

const { contextBridge, ipcRenderer } = require('electron')

contextBridge.exposeInMainWorld('api', {
  sendString: (str) => ipcRenderer.send('send-string', str),
  onStringResponse: (callback) => ipcRenderer.on('string-response', (event, response) => callback(response)),
  updatePresetList: () => {updatePresetList()}
})

ipcRenderer.on('portName', (event, data) => {
  document.getElementById('arduino').textContent = `arduino port: ${data}`
  
  console.log('port name: ', data)
})

ipcRenderer.on('noPort', (event, data) => {
  document.getElementById('arduino').textContent = `arduino not found`
})

let updatePresetList = () => {
  const presetList = document.getElementById('presetList')

  if (localStorage.length > 0) {
    presetList.textContent = ''

    for (let i = 0; i < localStorage.length; i++) {
        const key = localStorage.key(i)
        const value = localStorage.getItem(key)
        // console.log(`${key}: ${value}`)

        const outerDiv = document.createElement('div')
        outerDiv.style.cssText = `cursor:pointer; height:22px; border-bottom:2px solid rgba(0, 0, 0, 0.1);`
        outerDiv.id = `preset-${key}`

        const presetDiv = document.createElement('div')
        presetDiv.classList.add('preset', 'floatLeft')
        presetDiv.setAttribute('value', value)
        presetDiv.setAttribute('ref', `preset-${key}`)
        presetDiv.style.cssText = 'width:160px; padding:2px; padding-left: 4px;'
        presetDiv.textContent = key

        const deleteDiv = document.createElement('div')
        deleteDiv.classList.add('presetDelete', 'floatRight')
        deleteDiv.setAttribute('ref', `preset-${key}`)
        deleteDiv.style.cssText = 'margin-right:6px;'
        deleteDiv.textContent = 'x'

        outerDiv.appendChild(presetDiv)
        outerDiv.appendChild(deleteDiv)

        presetList.appendChild(outerDiv)
    }

    document.querySelectorAll('.preset').forEach(function(element) {
        element.addEventListener('click', function() {
            let presetName = element.getAttribute('ref').split('preset-').join('')
            let keyMapArr = localStorage.getItem(presetName)
            let keyMapString = 'km' + JSON.parse(keyMapArr).join(',')
            ipcRenderer.send('send-string', keyMapString)
        })
    })
    
    document.querySelectorAll('.presetDelete').forEach(function(element) {
        element.addEventListener('click', function() {
          let selectedPresetDiv = document.getElementById(element.getAttribute('ref'))
          selectedPresetDiv.style.display = 'none'

          selectedPreset = element.getAttribute('ref').split('preset-').join('')
          console.log(selectedPreset)
          localStorage.removeItem(selectedPreset)
        })
    })

  } else {
      presetList.innerHTML = '<span class="floatLeft" style="padding-left:4px; margin-top:4px;">no presets found</span>'
  }
}


ipcRenderer.on('keyMaps', (event, data) => {
  let presetName = document.getElementById('presetName').value
  localStorage.setItem(presetName, JSON.stringify(data))
  updatePresetList()
  document.getElementById('presetName').value = ''
})
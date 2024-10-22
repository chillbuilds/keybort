
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

ipcRenderer.on('presetLoaded', (event, data) => {
  document.getElementById('systemMsg').textContent = 'key map updated from preset list'
  
  setTimeout(()=>{
    document.getElementById('systemMsg').textContent = ''
  }, 2000)
})

ipcRenderer.on('keyUpdated', (event, data) => {
  document.getElementById('systemMsg').textContent = 'key updated'
  
  setTimeout(()=>{
    document.getElementById('systemMsg').textContent = ''
  }, 2000)
})

ipcRenderer.on('error', (event, data) => {
  document.getElementById('systemMsg').textContent = data
  
  setTimeout(()=>{
    document.getElementById('systemMsg').textContent = ''
  }, 2000)
})

let updatePresetList = () => {
  const presetList = document.getElementById('presetList')

  if (localStorage.length > 0) {
    presetList.textContent = ''

    for (let i = 0; i < localStorage.length; i++) {
        const key = localStorage.key(i)
        const value = localStorage.getItem(key)

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
            let keyMapString = 'km' + JSON.parse(keyMapArr).join('')
            ipcRenderer.send('send-string', keyMapString)
            document.getElementById('pageShade').style.display = 'none'
            document.getElementById('presetPopup').style.display = 'none'
            document.getElementById('systemMsg').textContent = 'updating key map from preset list'
        })
    })
    
    document.querySelectorAll('.presetDelete').forEach(function(element) {
        element.addEventListener('click', function() {
          let selectedPresetDiv = document.getElementById(element.getAttribute('ref'))
          selectedPresetDiv.style.display = 'none'

          selectedPreset = element.getAttribute('ref').split('preset-').join('')
          localStorage.removeItem(selectedPreset)
        })
    })

  } else {
      presetList.innerHTML = '<span class="floatLeft" style="padding-left:4px; margin-top:4px;">no presets found</span>'
  }
}

ipcRenderer.on('keyMaps', (event, data) => {
  let presetName = document.getElementById('presetName').value
  let formattedData = data
    formattedData.forEach((keyCode, index) => {
      if(keyCode.length < 3){
        formattedData[index] = '0' + keyCode
      }
    })
    localStorage.setItem(presetName, JSON.stringify(formattedData))
    updatePresetList()
    document.getElementById('presetName').value = ''
})
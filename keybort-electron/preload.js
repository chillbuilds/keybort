
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
  onStringResponse: (callback) => ipcRenderer.on('string-response', (event, response) => callback(response))
})

ipcRenderer.on('portName', (event, data) => {
  document.getElementById('arduino').textContent = `arduino port: ${data}`
  
  console.log('port name: ', data)
})

ipcRenderer.on('noPort', (event, data) => {
  document.getElementById('arduino').textContent = `arduino not found`
})

ipcRenderer.on('keyMaps', (event, data) => {
  let presetName = document.getElementById('presetName').value
  localStorage.setItem(presetName, JSON.stringify(data))
  
  const presetList = document.getElementById('presetList');

  if (localStorage.length > 0) {
      presetList.textContent = '';

      for (let i = 0; i < localStorage.length; i++) {
          const key = localStorage.key(i)
          const value = localStorage.getItem(key)
          console.log(`${key}: ${value}`)
          
          let lineStyling = ''
          if (i % 2 !== 0) {
              lineStyling = ' background:rgba(255,255,255,0.2); '
          }

          const divElement = document.createElement('div');
          divElement.style.cssText = `cursor:pointer; height:22px; ${lineStyling}`

          const keyDiv = document.createElement('div')
          keyDiv.classList.add('floatLeft')
          keyDiv.style.cssText = 'width:160px; padding:2px; padding-left: 4px;'
          keyDiv.textContent = key

          const valueDiv = document.createElement('div')
          valueDiv.classList.add('floatRight', 'deleteKeyMap')
          valueDiv.setAttribute('value', value)
          valueDiv.style.cssText = 'margin-right:6px;'
          valueDiv.textContent = 'x'

          divElement.appendChild(keyDiv)
          divElement.appendChild(valueDiv)

          presetList.appendChild(divElement)
      }
    } else {
        presetList.textContent = 'no presets found'
    }

  presetName.value = ''
})
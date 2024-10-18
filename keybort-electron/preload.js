/**
 * The preload script runs before `index.html` is loaded
 * in the renderer. It has access to web APIs as well as
 * Electron's renderer process modules and some polyfilled
 * Node.js functions.
 *
 * https://www.electronjs.org/docs/latest/tutorial/sandbox
 */

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
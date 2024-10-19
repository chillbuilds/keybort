const SerialPort = require('serialport').SerialPort;
const { app, BrowserWindow, ipcMain } = require('electron')
const path = require('node:path')
let mainWindow;

let portName = ''

let sendData = (data) => {
  const port = new SerialPort({ path: portName, baudRate: 9600 })
  port.on('open', () => {
  
    const sendDataBuffer = Buffer.from(data)
    const parsedData = Buffer.concat([sendDataBuffer])
  
    port.write(parsedData, (err) => {
      if (err) {
        return console.error('Error writing to port:', err.message)
      }
    })
  
    port.on('data', (data) => {
        console.log(data.toString())
      if(data.toString().includes("key updated")){
        console.log('updated key')
        port.close((err) => {
          if (err) {
            return console.error('Error closing port:', err.message)
          }
        })
      }
    })
  })
  
  port.on('error', (err) => {
    console.error('Error: ', err.message)
  })
}

function createWindow () {
  // Create the browser window.
  mainWindow = new BrowserWindow({
    width: 530,
    height: 480,
    webPreferences: {
      preload: path.join(__dirname, 'preload.js')
    },
    icon: path.join(__dirname, './public/images/keybort-icon.png')
  })

  // and load the index.html of the app.
  mainWindow.loadFile('index.html')

  // Open the DevTools.
  // mainWindow.webContents.openDevTools()
}

// This method will be called when Electron has finished
// initialization and is ready to create browser windows.
// Some APIs can only be used after this event occurs.
app.whenReady().then(() => {
  listSerialPorts()
  createWindow()
  app.on('activate', function () {
    // On macOS it's common to re-create a window in the app when the
    // dock icon is clicked and there are no other windows open.
    if (BrowserWindow.getAllWindows().length === 0) createWindow()
  })
})

// Quit when all windows are closed, except on macOS. There, it's common
// for applications and their menu bar to stay active until the user quits
// explicitly with Cmd + Q.
app.on('window-all-closed', function () {
  if (process.platform !== 'darwin') app.quit()
})

ipcMain.on('send-string', (event, str) => {
    if(str == 'send port'){
      listSerialPorts()
    }
    else{
      sendData(str)
    }
    console.log('Received string:', str)
})

async function listSerialPorts() {
  try {
    const ports = await SerialPort.list();
    portName = ''
    ports.forEach(port => {
      if(port.manufacturer.toLowerCase().includes("arduino")){
        portName = port.path
        mainWindow.webContents.send('portName', portName)
      }
    })
    if(portName == ''){
      mainWindow.webContents.send('noPort')
    }
  } catch (err) {
    console.error('Error listing serial ports:', err.message)
  }
}
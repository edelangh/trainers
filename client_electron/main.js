const {app, BrowserWindow} = require('electron')
const path = require('path')
const url = require('url')
const request = require('request')

var ipcMain = require('electron').ipcMain;


// Keep a global reference of the window object, if you don't, the window will
// be closed automatically when the JavaScript object is garbage collected.
let win


const API_URL = "http://localhost:8000"
global.sharedObj = {props: {
    test: undefined,
}};

ipcMain.on('submit', function(event, params) {
    console.log(params);
    request({method: 'POST', body: {
        test_id: global.sharedObj.props.test.id,
        test_answer: params.value,
        }, json: true, url: API_URL+'/api/answerTest'}, function (err, res, body) {
            console.log(body);
            event.sender.send('reply', body);
        });
});

function createWindow () {
  // Create the browser window.
  win = new BrowserWindow({width: 800, height: 600})

console.log(global.sharedObj.props);
  // and load the index.html of the app.
  win.loadURL(url.format({
    pathname: path.join(__dirname, 'index.html'),
    protocol: 'file:',
    slashes: true
  }))

  // Open the DevTools.
//  win.webContents.openDevTools()

  // Emitted when the window is closed.
  win.on('closed', () => {
    // Dereference the window object, usually you would store windows
    // in an array if your app supports multi windows, this is the time
    // when you should delete the corresponding element.
    win = null
  })
}

// This method will be called when Electron has finished
// initialization and is ready to create browser windows.
// Some APIs can only be used after this event occurs.
app.on('ready', launchTest)

// Quit when all windows are closed.
app.on('window-all-closed', () => {
  // On macOS it is common for applications and their menu bar
  // to stay active until the user quits explicitly with Cmd + Q
  if (process.platform !== 'darwin') {
    app.quit()
  }
})

function launchTest() {
    request({url: API_URL+'/api/randomTest'}, function (err, res, body) {
      global.sharedObj.props.test = JSON.parse(body);
      createWindow()
    });
}

app.on('activate', () => {
  // On macOS it's common to re-create a window in the app when the
  // dock icon is clicked and there are no other windows open.
  if (win === null) {
    launchTest();
  }
})

// In this file you can include the rest of your app's specific main process
// code. You can also put them in separate files and require them here.

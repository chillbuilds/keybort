$('#keyUpdateBtn').on('click', () => {
    // eeprom addresses
    // 1 - 8
    let keystroke = $('#keystroke').val()
    let modifier = 'sh'
    window.api.sendString(`${eepromAddress}${keystroke}${modifier}\n`)
    $('#popup').attr('style', 'display:none;')
    $('#pageShade').attr('style', 'display:none;')
    $('#keystroke').val('')
    $('#keyUpdate').attr('style', 'display:none;')
})

$('#rotaryUpdateBtn').on('click', () => {
    // eeprom addresses
    // 9, 10, 11
    if($('#rotaryLeftKey').val()){
        window.api.sendString(`09${$('#rotaryLeftKey').val()}sh\n`)
    }
    setTimeout(()=>{
        if($('#rotaryBtnKey').val()){
            window.api.sendString(`10${$('#rotaryBtnKey').val()}sh\n`)
        }
    }, 200)
    setTimeout(()=>{
        if($('#rotaryRightKey').val()){
            window.api.sendString(`11${$('#rotaryRightKey').val()}sh\n`)
        }
    }, 400)
    setTimeout(()=>{
        $('#rotaryLeftKey').val('')
        $('#rotaryBtnKey').val('')
        $('#rotaryRightKey').val('')
    }, 600)
    $('#popup').attr('style', 'display:none;')
    $('#pageShade').attr('style', 'display:none;')
    $('#rotaryUpdate').attr('style', 'display:none;')
})

$('#joystickUpdateBtn').on('click', () => {
    // eeprom addresses
    // 12, 13, 14, 15, 16
    let keystroke = $('#keystroke').val()
    let modifier = 'sh'
    window.api.sendString(`${eepromAddress}${keystroke}${modifier}\n`)
    $('#popup').attr('style', 'display:none;')
    $('#pageShade').attr('style', 'display:none;')
    $('#joystickUpdate').attr('style', 'display:none;')
})

$('#slidePotUpdateBtn').on('click', () => {
    // eeprom addresses
    // 17, 18
    setTimeout(()=>{
        if($('#slidePotLeftKey').val()){
            window.api.sendString(`17${$('#slidePotLeftKey').val()}sh\n`)
        }
    }, 200)
    setTimeout(()=>{
        if($('#slidePotRightKey').val()){
            window.api.sendString(`18${$('#slidePotRightKey').val()}sh\n`)
        }
    }, 400)
    $('#popup').attr('style', 'display:none;')
    $('#pageShade').attr('style', 'display:none;')
    $('#slidePotUpdate').attr('style', 'display:none;')
})
  
// Listen for the response from the main process
window.api.onStringResponse((response) => {
console.log('Response from main process:', response)
// You can update the UI with the response here
})
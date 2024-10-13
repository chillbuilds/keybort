$('#keyUpdateBtn').on('click', () => {
    // eeprom addresses
    // 1 - 8
    let keystroke = $('#keystroke').val()
    let modifier = $('input[name="modifier"]:checked').val()
    if(modifier){
        modifier = modifier.split('').shift()
    }else{
        modifier = '/'
    }
    window.api.sendString(`${eepromAddress}${keystroke}${modifier}\n`)
    $('#popup').attr('style', 'display:none;')
    $('#pageShade').attr('style', 'display:none;')
    $('#keystroke').val('')
    $('#keyUpdate').attr('style', 'display:none;')
    $('#keySpriteSrc').attr('src', `./public/images/key-sprites/keybort-sprite.png`)
    $('input[type="checkbox"]').prop('checked', false)
})

$('#rotaryUpdateBtn').on('click', () => {
    // eeprom addresses
    // 9, 10, 11
    let modifier = $('input[name="modifier"]:checked').val()
    if(modifier){
        modifier = modifier.split('').shift()
    }else{
        modifier = '/'
    }
    if($('#rotaryLeftKey').val()){
        window.api.sendString(`09${$('#rotaryLeftKey').val()}${modifier}\n`)
    }
    setTimeout(()=>{
        if($('#rotaryBtnKey').val()){
            window.api.sendString(`10${$('#rotaryBtnKey').val()}${modifier}\n`)
        }
    }, 200)
    setTimeout(()=>{
        if($('#rotaryRightKey').val()){
            window.api.sendString(`11${$('#rotaryRightKey').val()}${modifier}\n`)
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
    $('input[type="checkbox"]').prop('checked', false)
})

$('#joystickUpdateBtn').on('click', () => {
    // eeprom addresses
    // 12, 13, 14, 15, 16
    let modifier = $('input[name="modifier"]:checked').val()
    if(modifier){
        modifier = modifier.split('').shift()
    }else{
        modifier = '/'
    }
    setTimeout(()=>{
        if($('#joystickXMinusKey').val()){
            window.api.sendString(`12${$('#joystickXMinusKey').val()}${modifier}\n`)
        }
    }, 200)
    setTimeout(()=>{
        if($('#joystickXPlusKey').val()){
            window.api.sendString(`13${$('#joystickXPlusKey').val()}${modifier}\n`)
        }
    }, 400)
    setTimeout(()=>{
        if($('#joystickBtnKey').val()){
            window.api.sendString(`14${$('#joystickBtnKey').val()}${modifier}\n`)
        }
    }, 600)
    setTimeout(()=>{
        if($('#joystickYMinusKey').val()){
            window.api.sendString(`15${$('#joystickYMinusKey').val()}${modifier}\n`)
        }
    }, 800)
    setTimeout(()=>{
        if($('#joystickYPlusKey').val()){
            window.api.sendString(`16${$('#joystickYPlusKey').val()}${modifier}\n`)
        }
    }, 1000)
    $('#popup').attr('style', 'display:none;')
    $('#pageShade').attr('style', 'display:none;')
    $('#joystickUpdate').attr('style', 'display:none;')
    $('input[type="checkbox"]').prop('checked', false)
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
    $('#slidePotLeftKey').val('')
    $('#slidePotRightKey').val('')
    $('input[type="checkbox"]').prop('checked', false)
})
  
// Listen for the response from the main process
window.api.onStringResponse((response) => {
console.log('Response from main process:', response)
// You can update the UI with the response here
})
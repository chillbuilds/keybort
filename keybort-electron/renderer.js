window.api.sendString('send port')

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
    localStorage.setItem(eepromAddress, keystroke + modifier)
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
        localStorage.setItem('9', $('#rotaryLeftKey').val() + modifier)
    }
    setTimeout(()=>{
        if($('#rotaryBtnKey').val()){
            window.api.sendString(`10${$('#rotaryBtnKey').val()}${modifier}\n`)
            localStorage.setItem('10', $('#rotaryBtnKey').val() + modifier)
        }
    }, 100)
    setTimeout(()=>{
        if($('#rotaryRightKey').val()){
            window.api.sendString(`11${$('#rotaryRightKey').val()}${modifier}\n`)
            localStorage.setItem('11', $('#rotaryRightKey').val() + modifier)
        }
    }, 200)
    setTimeout(()=>{
        $('#rotaryLeftKey').val('')
        $('#rotaryBtnKey').val('')
        $('#rotaryRightKey').val('')
    }, 300)
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
            localStorage.setItem('12', $('#joystickXMinusKey').val() + modifier)
        }
    }, 100)
    setTimeout(()=>{
        if($('#joystickXPlusKey').val()){
            window.api.sendString(`13${$('#joystickXPlusKey').val()}${modifier}\n`)
            localStorage.setItem('13', $('#joystickXPlusKey').val() + modifier)
        }
    }, 200)
    setTimeout(()=>{
        if($('#joystickBtnKey').val()){
            window.api.sendString(`14${$('#joystickBtnKey').val()}${modifier}\n`)
            localStorage.setItem('14', $('#joystickBtnKey').val() + modifier)
        }
    }, 300)
    setTimeout(()=>{
        if($('#joystickYMinusKey').val()){
            window.api.sendString(`15${$('#joystickYMinusKey').val()}${modifier}\n`)
            localStorage.setItem('15', $('#joystickYMinusKey').val() + modifier)
        }
    }, 400)
    setTimeout(()=>{
        if($('#joystickYPlusKey').val()){
            window.api.sendString(`16${$('#joystickYPlusKey').val()}${modifier}\n`)
            localStorage.setItem('16', $('#joystickYPlusKey').val() + modifier)
        }
    }, 5000)
    $('#popup').attr('style', 'display:none;')
    $('#pageShade').attr('style', 'display:none;')
    $('#joystickUpdate').attr('style', 'display:none;')
    $('input[type="checkbox"]').prop('checked', false)
})

$('#slidePotUpdateBtn').on('click', () => {
    // eeprom addresses
    // 17, 18
    let modifier = $('input[name="modifier"]:checked').val()
    if(modifier){
        modifier = modifier.split('').shift()
    }else{
        modifier = '/'
    }
    setTimeout(()=>{
        if($('#slidePotLeftKey').val()){
            window.api.sendString(`17${$('#slidePotLeftKey').val()}${modifier}\n`)
            localStorage.setItem('17', $('#slidePotLeftKey').val() + modifier)
        }
    }, 100)
    setTimeout(()=>{
        if($('#slidePotRightKey').val()){
            window.api.sendString(`18${$('#slidePotRightKey').val()}${modifier}\n`)
            localStorage.setItem('18', $('#slidePotRightKey').val() + modifier)
        }
    }, 200)
    setTimeout(()=>{
        $('#slidePotLeftKey').val('')
        $('#slidePotRightKey').val('')
    },300)
    $('#popup').attr('style', 'display:none;')
    $('#pageShade').attr('style', 'display:none;')
    $('#slidePotUpdate').attr('style', 'display:none;')
    $('input[type="checkbox"]').prop('checked', false)
})

$('.mouseMode').on('click', function(){
    window.api.sendString(`12/m\n`)
    localStorage.setItem('mousemode', true)
    $('#popup').attr('style', 'display:none;')
    $('#pageShade').attr('style', 'display:none;')
    $('#joystickUpdate').attr('style', 'display:none;')
    $('#slidePotUpdate').attr('style', 'display:none;')
    $('input[type="checkbox"]').prop('checked', false)
})

$('.volumeMode').on('click', function(){
    window.api.sendString(`09/v\n`)
    $('#popup').attr('style', 'display:none;')
    $('#pageShade').attr('style', 'display:none;')
    $('#rotaryUpdate').attr('style', 'display:none;')
    $('input[type="checkbox"]').prop('checked', false)
})

$('#portRefresh').on('click', function(){
    window.api.sendString('send port')
})

$('#savePreset').on('click', function(){
    if($('#presetName').val()){
        $('#pageShade').attr('style', 'display:none;')
        $('#presetPopup').attr('style', 'display:none')
        window.api.sendString('send keys')
    }else{
        $('#presetName').focus()
        console.log('preset name is blank')
    }
})

// Listen for the response from the main process
window.api.onStringResponse((response) => {
console.log('Response from main process:', response)
// You can update the UI with the response here
})
let eepromAddress;
let key;

$('.key').on('click', function() {
    if($(this).attr('id') == 'key9'){
        // eepromAddress = `09`
        $('#popup').attr('style', 'display:inline-block;')
        $('#rotaryUpdate').attr('style', 'display:inline-block;')
        $('#pageShade').attr('style', 'display:inline-block;')
    }else
    if($(this).attr('id') == 'key10'){
        // eepromAddress = `10`
        $('#popup').attr('style', 'display:inline-block;')
        $('#joystickUpdate').attr('style', 'display:inline-block;')
        $('#pageShade').attr('style', 'display:inline-block;')
    }else
    if($(this).attr('id') == 'key11'){
        $('#popup').attr('style', 'display:inline-block;')
        $('#slidePotUpdate').attr('style', 'display:inline-block;')
        $('#pageShade').attr('style', 'display:inline-block;')
    }else{
        let selectedKey = $(this).attr('id').split('key')
        selectedKey = selectedKey.join('')
        if(selectedKey <= 9){
            eepromAddress = `0${selectedKey}`
        }else{
            eepromAddress = selectedKey
        }
        let keyAddress = $(this).attr('id').split('key').join('')
        $('#keySpriteSrc').attr('src', `./public/images/key-sprites/keybort-${keyAddress}.png`);
        $('#popup').attr('style', 'display:inline-block;')
        $('#keyUpdate').attr('style', 'display:inline-block;')
        $('#pageShade').attr('style', 'display:inline-block;')
        $('#keystroke').focus()
    }
})

$('#popupClose').on('click', () => {
    $('#keyUpdate').attr('style', 'display:none;')
    $('#rotaryUpdate').attr('style', 'display:none;')
    $('#joystickUpdate').attr('style', 'display:none;')
    $('#slidePotUpdate').attr('style', 'display:none;')
    $('#popup').attr('style', 'display:none;')
    $('#pageShade').attr('style', 'display:none;')
    $('#popupText').html('')
    $('#keystroke').val('')
})
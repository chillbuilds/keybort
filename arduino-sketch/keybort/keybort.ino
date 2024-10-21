// slide pot pinout
// 1 - vcc
// 2 - sig
// 3 - ground

#include <Keyboard.h>
#include <Mouse.h>
#include <EEPROM.h>

// saved key values
byte key1Val = EEPROM.read(1);
byte key2Val = EEPROM.read(2);
byte key3Val = EEPROM.read(3);
byte key4Val = EEPROM.read(4);
byte key5Val = EEPROM.read(5);
byte key6Val = EEPROM.read(6);
byte key7Val = EEPROM.read(7);
byte key8Val = EEPROM.read(8);
byte rotaryMinusVal = EEPROM.read(9);
byte rotaryBtnVal = EEPROM.read(10);
byte rotaryPlusVal = EEPROM.read(11);
byte joystickXMinusVal = EEPROM.read(12);
byte joystickXPlusVal = EEPROM.read(13);
byte joystickBtnVal = EEPROM.read(14);
byte joystickYMinusVal = EEPROM.read(15);
byte joystickYPlusVal = EEPROM.read(16);
byte slidePotMinusVal = EEPROM.read(17);
byte slidePotPlusVal = EEPROM.read(18);

// modifiers
byte key1Mod = EEPROM.read(19);
byte key2Mod = EEPROM.read(20);
byte key3Mod = EEPROM.read(21);
byte key4Mod = EEPROM.read(22);
byte key5Mod = EEPROM.read(23);
byte key6Mod = EEPROM.read(24);
byte key7Mod = EEPROM.read(25);
byte key8Mod = EEPROM.read(26);
byte rotaryMinusMod = EEPROM.read(27);
byte rotaryBtnMod = EEPROM.read(28);
byte rotaryPlusMod = EEPROM.read(29);
byte joystickXMinusMod = EEPROM.read(30);
byte joystickXPlusMod = EEPROM.read(31);
byte joystickBtnMod = EEPROM.read(32);
byte joystickYMinusMod = EEPROM.read(33);
byte joystickYPlusMod = EEPROM.read(34);
byte slidePotMinusMod = EEPROM.read(35);
byte slidePotPlusMod = EEPROM.read(36);

const int key1 = 10;
const int key2 = 16;
const int key3 = 14;
const int key4 = 15;
const int key5 = 5;
const int key6 = 4;
const int key7 = 3;
const int key8 = 2;

const int rotaryA = 6;
const int rotaryB = 7;
const int rotaryBtn = 8;

const int thumbBtn = 9;

const int joystickY = A1;
const int joystickX = A2;
const int slidePot = A3;

int rotaryCounter = 0;
int rotaryState;
int rotaryLastState;

int slidePotState;
int slidePotLastState;

int mouseSensitivity = 1;

unsigned long previousSystemDelayMillis = 0;
int systemDelayInterval = 500;
bool btnCooldown = false;

char address[2];
int key;
int modifier;

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  Mouse.begin();

  pinMode(rotaryA, INPUT);
  pinMode(rotaryB, INPUT);
  pinMode(rotaryBtn, INPUT_PULLUP);
  pinMode(thumbBtn, INPUT_PULLUP);
  pinMode(joystickX, INPUT);
  pinMode(joystickY, INPUT);
  pinMode(slidePot, INPUT);

  pinMode(key1, INPUT_PULLUP);
  pinMode(key2, INPUT_PULLUP);
  pinMode(key3, INPUT_PULLUP);
  pinMode(key4, INPUT_PULLUP);
  pinMode(key5, INPUT_PULLUP);
  pinMode(key6, INPUT_PULLUP);
  pinMode(key7, INPUT_PULLUP);
  pinMode(key8, INPUT_PULLUP);

  rotaryLastState = digitalRead(rotaryA);
  slidePotLastState = analogRead(slidePot);
}

void loop() {

  serialCheck();

  unsigned long systemDelayMillis = millis();

  if (systemDelayMillis - previousSystemDelayMillis >= systemDelayInterval) {
    previousSystemDelayMillis = systemDelayMillis;  // reset the timer

    slidePotState = analogRead(slidePot);

    if (!btnCooldown) {
      if (slidePotState <= slidePotLastState - 100) {
        previousSystemDelayMillis = systemDelayMillis;
        btnCooldown = true;
        if(joystickXMinusMod != 109){
          pressKey(slidePotMinusVal, slidePotMinusMod, 0);
        }
      } else if (slidePotState >= slidePotLastState + 100) {
        previousSystemDelayMillis = systemDelayMillis;
        btnCooldown = true;
        if(joystickXMinusMod != 109){
          pressKey(slidePotPlusVal, slidePotPlusMod, 0);
        }
      }

      if (btnCooldown) {
        slidePotLastState = slidePotState;
      }
    }

    if (btnCooldown) {
      // delay(systemDelayInterval);
      btnCooldown = false;
    }
  }

  int slidePotReading = analogRead(slidePot);

  mouseSensitivity = map(slidePotReading, 0, 1023, 1, 10);

  if(joystickXMinusMod == 109){
    if(analogRead(joystickX) > 486){
      Mouse.move(mouseSensitivity, 0, 0);
      delay(1);
    }
    if(analogRead(joystickX) < 482){
      Mouse.move(-(mouseSensitivity), 0, 0);
      delay(1);
    }
    if(analogRead(joystickY) > 530){
      Mouse.move(0, mouseSensitivity, 0);
      delay(1);
    }
    if(analogRead(joystickY) < 520){
      Mouse.move(0, -(mouseSensitivity), 0);
      delay(1);
    }

    if(digitalRead(thumbBtn) == LOW){
      Mouse.press(MOUSE_LEFT);
      Mouse.release(MOUSE_LEFT);
      Serial.println("pressed mouse left");
      delay(200);
    }
  }else{
    if (analogRead(joystickX) < 460){
      pressKey(joystickXMinusVal, joystickXMinusMod, 200);
    }
    if (analogRead(joystickX) > 500){
      pressKey(joystickXPlusVal, joystickXPlusMod, 200);
    }
    if(digitalRead(thumbBtn) == LOW){
      pressKey(joystickBtnVal, joystickBtnMod, 200);
    }
    if(analogRead(joystickY) > 545){
      pressKey(joystickYMinusVal, joystickYMinusMod, 200);
    }
    if(analogRead(joystickY) < 505){
      pressKey(joystickYPlusVal, joystickYPlusMod, 200);
    }
  }

  if(digitalRead(rotaryBtn) == LOW){
    // Mouse.press(MOUSE_RIGHT);
    // Mouse.release(MOUSE_RIGHT);
    pressKey(rotaryBtnVal, rotaryBtnMod, 300);
  }

  rotaryState = digitalRead(rotaryA);
  if (rotaryState != rotaryLastState) {
    if (digitalRead(rotaryB) != rotaryState) {
      rotaryCounter++;
      if (rotaryCounter >= 2) {
        rotaryCounter = 0;
        if(rotaryMinusMod == 118){
          Keyboard.press(128);
          // Keyboard.press(136);
          Keyboard.releaseAll();
        }else{
          pressKey(rotaryPlusVal, rotaryPlusMod, 0);
        }
      }
    } else {
      rotaryCounter--;
      if (rotaryCounter <= -2) {
        rotaryCounter = 0;
        if(rotaryMinusMod == 118){
          Keyboard.press(129);
          Keyboard.releaseAll();
        }else{
          pressKey(rotaryMinusVal, rotaryMinusMod, 0);
        }
      }
    }
    Serial.print("Position: ");
    Serial.println(rotaryCounter);
  }
  rotaryLastState = rotaryState;

  if (digitalRead(key1) == LOW) {
    pressKey(key1Val, key1Mod, 200);
  }
  if (digitalRead(key2) == LOW) {
    pressKey(key2Val, key2Mod, 200);
  }
  if (digitalRead(key3) == LOW) {
    pressKey(key3Val, key3Mod, 200);
  }
  if (digitalRead(key4) == LOW) {
    pressKey(key4Val, key4Mod, 200);
  }
  if (digitalRead(key5) == LOW) {
    pressKey(key5Val, key5Mod, 200);
  }
  if (digitalRead(key6) == LOW) {
    pressKey(key6Val, key6Mod, 200);
  }
  if (digitalRead(key7) == LOW) {
    pressKey(key7Val, key7Mod, 200);
  }
  if (digitalRead(key8) == LOW) {
    pressKey(key8Val, key8Mod, 200);
  }
}

void serialCheck() {
  if (Serial.available() > 0) {

    String incomingString = Serial.readStringUntil('\n');

    String keyMapCheck = incomingString.substring(0, 2);

    if(incomingString == "send keys"){
      sendKeyMappings();
    }else if(keyMapCheck == "km"){
      String keys = incomingString.substring(2);

      int eepromAddress = 1;

      for(int i = 0; i < 108; i = i+3){
        String asciiCodeStr = (String)keys[i] + (String)keys[i+1] + (String)keys[i+2];
        int asciiCodeInt = asciiCodeStr.toInt();
        EEPROM.write(eepromAddress, asciiCodeInt);
        eepromAddress++;
      }-+-+-+-+
      Serial.print("preset updated");
    }else{
      int serialIntArray[4];
      String serialStringArray[4];

      for (int i = 0; i < 4; i++) {
        serialIntArray[i] = (int)incomingString.charAt(i);
        serialStringArray[i] = incomingString.charAt(i);
      }

      // update key
      String parsedAddress = serialStringArray[0] + serialStringArray[1];
      int addressInt = parsedAddress.toInt();

      Serial.print("address: ");
      Serial.println(addressInt);

      modifier = (int)serialIntArray[3];
      Serial.print("modifier: ");
      Serial.println((int)modifier);

      EEPROM.write(addressInt, (int)serialIntArray[2]);
      EEPROM.write(addressInt + 18, modifier);
      Serial.println("key updated");

      if (addressInt == 1) {
        key1Val = (byte)serialIntArray[2];
        key1Mod = (byte)serialIntArray[3];
      }
      if (addressInt == 2) {
        key2Val = (byte)serialIntArray[2];
        key2Mod = (byte)serialIntArray[3];
      }
      if (addressInt == 3) {
        key3Val = (byte)serialIntArray[2];
        key3Mod = (byte)serialIntArray[3];
      }
      if (addressInt == 4) {
        key4Val = (byte)serialIntArray[2];
        key4Mod = (byte)serialIntArray[3];
      }
      if (addressInt == 5) {
        key5Val = (byte)serialIntArray[2];
        key5Mod = (byte)serialIntArray[3];
      }
      if (addressInt == 6) {
        key6Val = (byte)serialIntArray[2];
        key6Mod = (byte)serialIntArray[3];
      }
      if (addressInt == 7) {
        key7Val = (byte)serialIntArray[2];
        key7Mod = (byte)serialIntArray[3];
      }
      if (addressInt == 8) {
        key8Val = (byte)serialIntArray[2];
        key8Mod = (byte)serialIntArray[3];
      }
      if (addressInt == 9) {
        rotaryMinusVal = (byte)serialIntArray[2];
        rotaryMinusMod = (byte)serialIntArray[3];
      }
      if (addressInt == 10) {
        rotaryBtnVal = (byte)serialIntArray[2];
        rotaryBtnMod = (byte)serialIntArray[3];
      }
      if (addressInt == 11) {
        rotaryPlusVal = (byte)serialIntArray[2];
        rotaryPlusMod = (byte)serialIntArray[3];
      }
      if (addressInt == 12) {
        joystickXMinusVal = (byte)serialIntArray[2];
        joystickXMinusMod = (byte)serialIntArray[3];
      }
      if (addressInt == 13) {
        joystickXPlusVal = (byte)serialIntArray[2];
        joystickXPlusMod = (byte)serialIntArray[3];
      }
      if (addressInt == 14) {
        joystickBtnVal = (byte)serialIntArray[2];
        joystickBtnMod = (byte)serialIntArray[3];
      }
      if (addressInt == 15) {
        joystickYMinusVal = (byte)serialIntArray[2];
        joystickYMinusMod = (byte)serialIntArray[3];
      }
      if (addressInt == 16) {
        joystickYPlusVal = (byte)serialIntArray[2];
        joystickYPlusMod = (byte)serialIntArray[3];
      }
      if (addressInt == 17) {
        slidePotMinusVal = (byte)serialIntArray[2];
        slidePotMinusMod = (byte)serialIntArray[3];
      }
      if (addressInt == 18) {
        slidePotPlusVal = (byte)serialIntArray[2];
        slidePotPlusMod = (byte)serialIntArray[3];
      }
    }
  }
}

void pressKey(int keyVal, int keyMod, int keyDelay) {
  if (keyMod == 99) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.write(keyVal);
  } else if (keyMod == 97) {
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.write(keyVal);
  } else if (keyMod == 115) {
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.write(keyVal);
  } else {
    Keyboard.write(keyVal);
  }
  Keyboard.releaseAll();
  delay(keyDelay);
}

void sendKeyMappings() {
  byte keysAndMods[36] = {key1Val, key2Val, key3Val, key4Val, key5Val, key6Val, key7Val, key8Val ,rotaryMinusVal, rotaryBtnVal, rotaryPlusVal, joystickXMinusVal, joystickXPlusVal, joystickBtnVal, joystickYMinusVal, joystickYPlusVal, slidePotMinusVal, slidePotPlusVal, key1Mod, key2Mod, key3Mod, key4Mod, key5Mod, key6Mod, key7Mod, key8Mod, rotaryMinusMod, rotaryBtnMod, rotaryPlusMod, joystickXMinusMod, joystickXPlusMod, joystickBtnMod, joystickYMinusMod, joystickYPlusMod, slidePotMinusMod, slidePotPlusMod};
  String keyArr = "keys:";
  for(int i = 0; i < 36; i++){
    if(i == 35){
      keyArr = keyArr + keysAndMods[i];
    }else{
      keyArr = keyArr + keysAndMods[i] + ",";
    }
  }
  Serial.println(keyArr);

}
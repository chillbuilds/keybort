// slide pot pinout
// 1 - vcc
// 2 - sig
// 3 - ground

#include <Keyboard.h>
#include <Mouse.h>
#include <EEPROM.h>
// read saved key values
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
byte slidePotMinusVal = EEPROM.read(17);
byte slidePotPlusVal = EEPROM.read(18);

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
char modifier[2];

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

  unsigned long systemDelayMillis = millis();

  if (systemDelayMillis - previousSystemDelayMillis >= systemDelayInterval) {
      previousSystemDelayMillis = systemDelayMillis;  // reset the timer

      slidePotState = analogRead(slidePot);

      Serial.print("slidePotState: ");
      Serial.println(slidePotState);
      Serial.print("slidePotLastState: ");
      Serial.println(slidePotLastState);

      if(!btnCooldown){
          if(slidePotState <= slidePotLastState - 100){
              btnCooldown = true;
              Keyboard.write(slidePotMinusVal);
          }else if(slidePotState >= slidePotLastState + 100){
              btnCooldown = true;
              Keyboard.write(slidePotPlusVal);
          }

          if(btnCooldown){
              slidePotLastState = slidePotState;
          }
      }

      if(btnCooldown){
          delay(systemDelayInterval);
          btnCooldown = false;
      }
  }
  
  int slidePotReading = analogRead(slidePot);

  mouseSensitivity = map(slidePotReading, 0, 1023, 1, 10);

  serialCheck();

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

  if(digitalRead(rotaryBtn) == LOW){
    // Mouse.press(MOUSE_RIGHT);
    // Mouse.release(MOUSE_RIGHT);
    Keyboard.write(rotaryBtnVal);
    Serial.println("pressed mouse right");
    delay(300);
  }

  rotaryState = digitalRead(rotaryA);
 if (rotaryState != rotaryLastState){     
  if (digitalRead(rotaryB) != rotaryState) { 
    rotaryCounter ++;
    if(rotaryCounter >= 2){
      rotaryCounter = 0;
      Keyboard.write(rotaryPlusVal);
    }
  } else {
    rotaryCounter --;
    if(rotaryCounter < -1){
      rotaryCounter = 0;
      Keyboard.write(rotaryMinusVal);
    }
  }
  Serial.print("Position: ");
  Serial.println(rotaryCounter);
  } 
  rotaryLastState = rotaryState;
  if(digitalRead(key1) == LOW){
    Keyboard.write(key1Val);
    delay(200);
  }
  if(digitalRead(key2) == LOW){
    Keyboard.write(key2Val);
    delay(200);
  }
  if(digitalRead(key3) == LOW){
    Keyboard.write(key3Val);
    delay(200);
  }
  if(digitalRead(key4) == LOW){
    Keyboard.write(key4Val);
    delay(200);
  }
  if(digitalRead(key5) == LOW){
    Keyboard.write(key5Val);
    delay(200);
  }
  if(digitalRead(key6) == LOW){
    Keyboard.write(key6Val);
    delay(200);
  }
  if(digitalRead(key7) == LOW){
    Keyboard.write(key7Val);
    delay(200);
  }
  if(digitalRead(key8) == LOW){
    Keyboard.write(key8Val);
    delay(200);
  }

}

void serialCheck() {
  if (Serial.available() > 0) {
    
    String incomingString = Serial.readStringUntil('\n');
    int serialIntArray[5];
    String serialStringArray[5];

    for(int i = 0; i < 5; i++){
      serialIntArray[i] = (int)incomingString.charAt(i);
      serialStringArray[i] = incomingString.charAt(i);
    }

    // update key
    String parsedAddress = serialStringArray[0] + serialStringArray[1];
    int addressInt = parsedAddress.toInt();

    Serial.print("address: ");
    Serial.println(addressInt);

    EEPROM.write(addressInt, (int)serialIntArray[2]);
    Serial.println("key updated");

    if(addressInt == 1){
      key1Val = (byte)serialIntArray[2];
    }
    if(addressInt == 2){
      key2Val = (byte)serialIntArray[2];
    }
    if(addressInt == 3){
      key3Val = (byte)serialIntArray[2];
    }
    if(addressInt == 4){
      key4Val = (byte)serialIntArray[2];
    }
    if(addressInt == 5){
      key5Val = (byte)serialIntArray[2];
    }
    if(addressInt == 6){
      key6Val = (byte)serialIntArray[2];
    }
    if(addressInt == 7){
      key7Val = (byte)serialIntArray[2];
    }
    if(addressInt == 8){
      key8Val = (byte)serialIntArray[2];
    }
    if(addressInt == 9){
      rotaryMinusVal = (byte)serialIntArray[2];
    }
    if(addressInt == 10){
      rotaryBtnVal = (byte)serialIntArray[2];
    }
    if(addressInt == 11){
      rotaryPlusVal = (byte)serialIntArray[2];
    }
    if(addressInt == 17){
      slidePotMinusVal = (byte)serialIntArray[2];
    }
    if(addressInt == 18){
      slidePotPlusVal = (byte)serialIntArray[2];
    }

  }
}
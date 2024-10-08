// slide pot pinout
// 1 - vcc
// 2 - sig
// 3 - ground

#include <Keyboard.h>
#include <Mouse.h>
#include <EEPROM.h>

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
}

void loop() {

  if(analogRead(joystickX) > 486){
    Mouse.move(1, 0, 0);
    delay(1);
  }
  if(analogRead(joystickX) < 482){
    Mouse.move(-1, 0, 0);
    delay(1);
  }
  if(analogRead(joystickY) > 530){
    Mouse.move(0, 1, 0);
    delay(1);
  }
  if(analogRead(joystickY) < 520){
    Mouse.move(0, -1, 0);
    delay(1);
  }
  
  if(digitalRead(thumbBtn) == LOW){
    Mouse.press(MOUSE_LEFT);
    Mouse.release(MOUSE_LEFT);
    Serial.println("pressed mouse left");
    delay(200);
  }

  if(digitalRead(rotaryBtn) == LOW){
    Mouse.press(MOUSE_RIGHT);
    Mouse.release(MOUSE_RIGHT);
    Serial.println("pressed mouse right");
    delay(200);
  }

  rotaryState = digitalRead(rotaryA); // Reads the "current" state of the outputA
  // If the previous and the current state of the outputA are different, that means a Pulse has occured
  if (rotaryState != rotaryLastState){     
    // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
    if (digitalRead(rotaryB) != rotaryState) { 
      rotaryCounter ++;
    } else {
      rotaryCounter --;
    }
    Serial.print("Position: ");
    Serial.println(rotaryCounter);
  } 
  rotaryLastState = rotaryState;

  if(digitalRead(key1) == LOW){
    Serial.println("key 1 pressed");
    delay(200);
  }
  if(digitalRead(key2) == LOW){
    Serial.println("key 2 pressed");
    delay(200);
  }
  if(digitalRead(key3) == LOW){
    Serial.println("key 3 pressed");
    delay(200);
  }
  if(digitalRead(key4) == LOW){
    Serial.println("key 4 pressed");
    delay(200);
  }
  if(digitalRead(key5) == LOW){
    Serial.println("key 5 pressed");
    delay(200);
  }
  if(digitalRead(key6) == LOW){
    Serial.println("key 6 pressed");
    delay(200);
  }
  if(digitalRead(key7) == LOW){
    Serial.println("key 7 pressed");
    delay(200);
  }
  if(digitalRead(key8) == LOW){
    Serial.println("key 8 pressed");
    delay(200);
  }

}

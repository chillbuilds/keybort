#include <EEPROM.h>

bool receivingData = false;
bool addressReceived = false;
bool keyReceived = false;

char address[2];
char key;
char modifier[4];

int arrIndex = 0;

void setup() {
  Serial.begin(9600);

  // EEPROM.write(0, valueToSave);
}

void loop() {
  // byte value = EEPROM.read(0);
  // Serial.print("Value at EEPROM address 0: ");
  // Serial.println(value);
  // delay(10000);

  if (Serial.available() > 0) {
    
    char incomingByte = Serial.read();

    if(receivingData == true && addressReceived == false){
      address[arrIndex] = incomingByte;
      arrIndex++;
    }
    if(receivingData == true && addressReceived == true && keyReceived == false){
      key = (int)incomingByte;
      keyReceived = true;
    }
    if(receivingData == true && addressReceived == true && keyReceived == true){
      modifier[arrIndex] = (int)incomingByte;
      arrIndex++;
    }
    if(incomingByte == 126){
      receivingData = true;
    }
//                   hyphen
    if(incomingByte == 45){
      addressReceived = true;
      arrIndex = 0;
    }
//                 underscore
    if(incomingByte == 95){
      keyReceived = true;
    }

    if(incomingByte == 96){
      updateKey();
      receivingData = false;
      addressReceived = false;
      arrIndex = 0;
    }

    Serial.print(incomingByte);
  }
}

void updateKey() {
  String parsedAddress = String(address[0]) + String(address[1]);
  int addressInt = parsedAddress.toInt();

  // Serial.println(EEPROM.read(12));
  EEPROM.write(addressInt, (int)key);
  Serial.println("key updated");

  // Serial.println("");
  // Serial.print("modifier: ");
  // Serial.print((int)modifier[0]);
  // Serial.print(", ");
  // Serial.print((int)modifier[1]);
}
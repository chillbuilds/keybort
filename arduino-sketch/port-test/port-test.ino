#include <EEPROM.h>

bool receivingData = false;
bool addressReceived = false;
bool keyReceived = false;

char address[2];
char key[2];
char modifier[2];

int arrIndex = 0;

void setup() {
  Serial.begin(9600);

  byte valueToSave = 42;

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
      key[arrIndex] = (int)incomingByte;
      arrIndex++;
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
      arrIndex = 0;
    }

    if(incomingByte == 96){
      updateKey();
      receivingData = false;
      addressReceived = false;
      arrIndex = 0;
    }

    // Serial.print(incomingByte);
  }
}

void updateKey() {
  String parsedAddress = String(address[0]) + String(address[1]);
  int addressInt = parsedAddress.toInt();

  Serial.println(EEPROM.read(12));
  // EEPROM.write(addressInt, (int)key[0]);
  // Serial.println("updated address");

  // Serial.println("");
  // Serial.print("address: ");
  // Serial.print(address[0]);
  // Serial.print(", ");
  // Serial.print(address[1]);

  // Serial.println("");
  // Serial.print("key: ");
  // Serial.print((int)key[0]);
  // Serial.print(", ");
  // Serial.print((int)key[1]);

  // Serial.println("");
  // Serial.print("modifier: ");
  // Serial.print((int)modifier[0]);
  // Serial.print(", ");
  // Serial.print((int)modifier[1]);
}
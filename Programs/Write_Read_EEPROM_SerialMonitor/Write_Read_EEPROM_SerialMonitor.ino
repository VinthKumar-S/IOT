#include <EEPROM.h>

int address;
int dataToWrite;
void setup() {
  Serial.begin(9600);
}
void loop() {

  String buffer=" ";
  buffer=Serial.readString();
  if(buffer.startsWith("read")){
  address=buffer.substring(buffer.indexOf(' ')+1).toInt();
  Serial.print("Data from the Address: ");
  Serial.print(address);
  Serial.println();
  Serial.println(EEPROM.read(address));
  }

  else if(buffer.startsWith("write")){
  address=buffer.substring(6,7).toInt();
  dataToWrite=buffer.substring(8).toInt();
  Serial.print("Written: ");
  Serial.print(dataToWrite);
  Serial.println();
  Serial.print("to the Address: ");
  Serial.print(address);
  Serial.println();
  Serial.println(EEPROM.read(address));
  EEPROM.write(address,dataToWrite);
      
  }
  }

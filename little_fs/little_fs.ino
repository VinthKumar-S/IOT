#include "LittleFS.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  if(!LittleFS.begin()){
    Serial.println("An Error has occurred while mouting LittleFS");
    return;
  }

  File file = LittleFS.open("/test_f.txt","r");

  if(!file){
    Serial.println("Failed to open file for reading");

    return;
  }

  Serial.println("File Content:");
  while(file.available()){
    Serial.write(file.read());
  }
  file.close();
}



void loop() {
  // put your main code here, to run repeatedly:

}

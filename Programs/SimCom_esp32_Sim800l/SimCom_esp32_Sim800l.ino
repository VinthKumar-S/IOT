#include <SoftwareSerial.h>


const int rxPin = 16;
const int txPin = 17;

SoftwareSerial sim800l(rxPin,txPin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  sim800l.begin(115200);

  sim800l.println("AT+CGATT?");
  delay(1000);

  if(sim800l.available()>0){
    String response = "";
    while(sim800l.available()>0){
      response += (char)sim800l.read();
    }
    if(response.indexOf("OK") != -1){
      Serial.println("SIM800L connected");
    }else{
      Serial.println("SIM800L not connected");
    }
  }
  else{
    Serial.println("SIM800L not responding");
  }
}

void loop() {

}

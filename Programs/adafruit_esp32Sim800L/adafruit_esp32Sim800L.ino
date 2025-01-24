#include "Adafruit_FONA.h"

#define SIM800L_RX 27
#define SIM800L_TX 26
#define SIM800L_PWRKEY 4
#define SIM800L_RST 5
#define SIM800L_POWER 23

char replaybuffer[255];

HardwareSerial *sim800lSerial = &Serial1;
Adafruit_FONA sim800l = Adafruit_FONA(SIM800L_PWRKEY);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(F("Initializing GSM SIM800L..."));

  initializeSIM800L();

}

void initializeSIM800L(){
  sim800lSerial->begin(9600,SERIAL_8N1,SIM800L_TX,SIM800L_RX);
  if(!sim800l.begin(*sim800lSerial)){
    Serial.println(F("Couldn't find GSM SIM800L"));
    while(1);
  }
  Serial.println(F("GSM SIM800l is OK"));

  char imei[16] = {0};
  uint8_t imeiLen = sim800l.getIMEI(imei);
  if(imeiLen>0){
    Serial.print("SIM card IMEI: ");
    Serial.println(imei);
  }

  sim800lSerial->print("AT+CNMI=2,1\r\n");
}

void loop() {
  // put your main code here, to run repeatedly:

}

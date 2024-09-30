#include "protocentralAds1292r.h"
#include "ecgRespirationAlgo.h"
#include <SPI.h>

volatile uint8_t globalHeartRate = 0;
volatile uint8_t globalRespirationRate = 0;

const int d_pin = 2;
const int c_pin = 10;
const int s_pin = 3;
const int p_pin = 4;

int16_t ecgWaveBuff, ecgFilterout;
int16_t resWaveBuff, respFilterout;

ads1292r ADS1292R;
ecg_respiration_algorithm ECG_RESPIRATION_ALGORITHM;

void setup() {
  // put your setup code here, to run once:
  delay(2000);

  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.setDataMode(SPI_MODE1);
  SPI.setBitOrder(MSBFIRST);

  pinMode(d_pin,INPUT);
  pinMode(c_pin,OUTPUT);
  pinMode(s_pin,OUTPUT);
  pinMode(p_pin,OUTPUT);

  Serial.begin(9600);

  ADS1292R.ads1292Init(c_pin,p_pin,s_pin);
}

void loop() {
  ads1292OutputValues ecgRespirationValues;

  boolean ret = ADS1292R.getAds1292EcgAndRespirationSamples(d_pin,c_pin,&ecgRespirationValues);
  // put your main code here, to run repeatedly:
  if(ret == true){
    ecgWaveBuff =(int16_t)(ecgRespirationValues.sDaqVals[1] >> 8);
    resWaveBuff =(int16_t)(ecgRespirationValues.sresultTempResp >> 8);

    if(ecgRespirationValues.leadoffDetected == false){
      Serial.println("Lead-off not detected. Processing ECG data.");
      ECG_RESPIRATION_ALGORITHM.ECG_ProcessCurrSample(&ecgWaveBuff, &ecgFilterout);
      ECG_RESPIRATION_ALGORITHM.QRS_Algorithm_Interface(ecgFilterout,&globalHeartRate);
      
    }
    else{
       Serial.println("Lead-off detected. Check electrode connections.");
      ecgFilterout =0;
      respFilterout =0;
    }

    Serial.println(ecgFilterout);
  }
}

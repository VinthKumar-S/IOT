#define TINY_GSM_MODEM_SIM800

#include <TinyGsmClient.h>
#include <SoftwareSerial.h>

#define MODEM_RST 5
#define MODEM_PWRKEY 4
#define MODEM_POWER_ON 23
#define MODEM_TX 27
#define MODEM_RX 26
#define LED_BUILTIN 2 

#define SerialMon Serial

#define SerialAT Serial1

TinyGsm modem(SerialAT);
TinyGsmClient gsmClient;

void setup() {
  // put your setup code here, to run once:
  SerialMon.begin(115200);

  pinMode(LED_BUILTIN,OUTPUT);

  pinMode(MODEM_PWRKEY,OUTPUT);
  pinMode(MODEM_RST,OUTPUT);
  pinMode(MODEM_POWER_ON,OUTPUT);

  digitalWrite(MODEM_PWRKEY,HIGH);
  digitalWrite(MODEM_POWER_ON,HIGH);

  SerialAT.begin(115200,SERIAL_8N1,MODEM_RX,MODEM_TX);
  delay(3000);

  SerialMon.println("Initializing modem...");
  modem.restart();

  if(modem.testAT()){
    SerialMon.println("Modem is ready!");
  }else{
    SerialMon.println("Failed to initialize modem.");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN,HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN,LOW);
  delay(500);

} 

// #define LED_BUILTIN 2 // Onboard LED pin

// void setup() {
//   pinMode(LED_BUILTIN, OUTPUT); // Set LED pin as output
// }

// void loop() {
//   digitalWrite(LED_BUILTIN, HIGH); // Turn the LED on
//   delay(1000);                     // Wait for 1 second
//   digitalWrite(LED_BUILTIN, LOW);  // Turn the LED off
//   delay(1000);                     // Wait for 1 second
// }
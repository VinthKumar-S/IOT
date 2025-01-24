#define MODEM_RST       5
#define MODEM_PWKEY     4
#define MODEM_POWER_ON  23
#define MODEM_TX        27
#define MODEM_RX        26

#define SerialMon Serial 
#define SerialAT Serial1

#define TINY_GSM_MODEM_SIM800
#define TINY_GSM_RX_BUFFER  1024

#include <TinyGsmClient.h>

TinyGsm modem(SerialAT);

void setup() {
  // put your setup code here, to run once:
  SerialMon.begin(115200);

  pinMode(MODEM_PWKEY,OUTPUT);
  pinMode(MODEM_RST,OUTPUT);
  pinMode(MODEM_POWER_ON,OUTPUT);
  digitalWrite(MODEM_PWKEY,LOW);
  digitalWrite(MODEM_RST,HIGH);
  digitalWrite(MODEM_POWER_ON,HIGH);

  SerialAT.begin(115200,SERIAL_8N1,MODEM_RX,MODEM_TX);
  delay(3000);

  SerialMon.println("Initializing modem...");
  modem.restart(); 
}

void loop() {
  // put your main code here, to run repeatedly:
  if(checkNetworkConnection()){
    SerialMon.print("Connected...");
  }else{
    SerialMon.println("Modem is not connected to the network,SMS not sent");
  }
  delay(10000);
}

bool checkNetworkConnection(){
  if(modem.isNetworkConnected()){
    SerialMon.println("Modem is connected to the network..");
    return true;
  }else{
    SerialMon.println("Modem is not connected to the network.");
    int signalQuality = modem.getSignalQuality();
    SerialMon.print("Signal Quality: ");
    SerialMon.println(signalQuality);
    return false;
  }
}

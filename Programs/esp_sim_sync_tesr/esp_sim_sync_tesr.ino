#define TINY_GSM_MODEM_SIM800

#include <TinyGsmClient.h>
 // Define the GSM modem model

#define SerialMon Serial
#define SerialAT Serial1 // Corrected from 'Seral1' to 'Serial1'

#define MODEM_BAUD 9600

// Define RX and TX pins for the SIM800L
#define MODEM_RX 16 // Change to your RX pin
#define MODEM_TX 17 // Change to your TX pin

TinyGsm modem(SerialAT);

void setup() {
  SerialMon.begin(115200); // Initialize Serial Monitor
  SerialAT.begin(MODEM_BAUD, SERIAL_8N1, MODEM_RX, MODEM_TX); // Corrected 'being' to 'begin'
  
  modem.restart(); // Restart the modem

  // Check SIM card status
  if (modem.getSimStatus() != 3) {
    SerialMon.println("SIM card is not ready."); // Added missing semicolon
  } else {
    SerialMon.println("SIM card is ready.");
  }

  // Get SIM card number
  String simCardNumber;
    modem.sendAT("+CCID");
    simCardNumber = modem.waitResponse();  // Corrected 'senAT' to 'sendAT'
    //simCardNumber = modem.getResponse();
    SerialMon.println("SIM Card Number: " + simCardNumber);
  

  // Measure signal strength
  String signalQuality;
    modem.sendAT("+CSQ");
    signalQuality = modem.waitResponse();  // Corrected 'sendAT' to 'sendAT'
    //signalQuality = modem.getResponse(); // Corrected 'getRespose' to 'getResponse'
    SerialMon.println("Signal Quality: " + signalQuality);
  
}

void loop() {
  // Your main code here
}
#define TINY_GSM_MODEM_SIM800

#include <TinyGsmClient.h>

#define SIM800L_TX 27
#define SIM800L_RX 26
#define SIM800L_PWRKEY 4
#define SerialMon Serial
#define SerialAT Serial1

// Define your recipient phone number
const char phoneNumber[] = "+918220201647";
// Define the message to send
const char smsMessage[] = "Hello from ESP32 TTGO!";

// Create modem object
TinyGsm modem(SerialAT);

void setup() {
  // Start Serial monitor
  SerialMon.begin(115200);
  delay(10);

  // Power on SIM800L
  pinMode(SIM800L_PWRKEY, OUTPUT);
  digitalWrite(SIM800L_PWRKEY, LOW);
  delay(1000);
  digitalWrite(SIM800L_PWRKEY, HIGH);

  // Begin Serial communication with SIM800L
  SerialAT.begin(9600, SERIAL_8N1, SIM800L_RX, SIM800L_TX);
  delay(3000);

  SerialMon.println("Initializing modem...");
  if (!modem.restart()) {
    SerialMon.println("Failed to restart modem");
    while (true);
  }
  SerialMon.println("Modem initialized");

  // Check signal quality
  int signalQuality = modem.getSignalQuality();
  SerialMon.print("Signal Quality: ");
  SerialMon.println(signalQuality);

  // Send SMS
  SerialMon.println("Sending SMS...");
  if (modem.sendSMS(phoneNumber, smsMessage)) {
    SerialMon.println("SMS sent successfully!");
  } else {
    SerialMon.println("Failed to send SMS.");
  }
}

void loop() {
  // Do nothing in the loop
}

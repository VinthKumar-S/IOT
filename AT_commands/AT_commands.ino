#define RX_PIN 16
#define TX_PIN 17
#define SIM800L_BAUD 9600


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(SIM800L_BAUD,SERIAL_8N1,RX_PIN,TX_PIN);

  delay(3000);

  sendATCommand("AT");
  delay(1000);

  
  sendATCommand("AT+CMGF=1");
  delay(1000);

  sendATCommand("AT+CPIN?");
  delay(1000);

  sendATCommand("AT+CSQ");
  delay(1000);

  Serial2.println("AT+CMCS=\"+1234567890\"");
  delay(1000);

  Serial2.println("Hello from ESP32 using AT commands!");
  delay(1000);

  Serial2.write(26);
  delay(1000);

  Serial.println("SMS Sent");
}

void loop() {
  // put your main code here, to run repeatedly:

}

void sendATCommand(String cmd){
  Serial.println("Sending command: "+cmd);
  Serial2.println(cmd);
  delay(100);
  while(Serial2.available()){
    String response = Serial2.readStringUntil('\n');
    Serial.println(response);
  }
}

#define RX_PIN 16
#define TX_PIN 17
#define SIM800L_BAUD 9600
#define LED_PIN 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(SIM800L_BAUD,SERIAL_8N1,RX_PIN,TX_PIN);
  pinMode(LED_PIN,OUTPUT);

  delay(3000);

  if(sendATCommand("AT")){
    blinkLED(3);
  }else{
    digitalWrite(LED_PIN,LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(LED_PIN,HIGH);
    delay(500);
    digitalWrite(LED_PIN,LOW);
    delay(500);

}

bool sendATCommand(String cmd){
  Serial2.println(cmd);
  delay(100);

  String response = "";
  while(Serial2.available()){
    response += char(Serial2.read());
  }

  Serial.println(response);

  return response.indexOf("OK") != -1;
}

void blinkLED(int times){
  for(int i=0;i<times;i++){
    digitalWrite(LED_PIN,HIGH);
    delay(500);
    digitalWrite(LED_PIN,LOW);
    delay(500);
    
  }
}
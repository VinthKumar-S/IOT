#include <ESP8266WiFi.h>

const char *ssid = "SMV Network";
const char *pass = "hmax8875";

WiFiClient client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(10);

  WiFi.begin(ssid,pass);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");  
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:

}

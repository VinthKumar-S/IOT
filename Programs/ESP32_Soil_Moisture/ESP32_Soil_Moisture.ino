#include <WiFi.h>
#include <WiFiClient.h>
#include <IOXhop_FirebaseESP32.h>
#define sensor 33
#define FIREBASE_HOST "esp32-test-8eea4-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "W7MeD1nAYqeDiBgfnNVRcZIiSVJNydh4RcmcLH6L"


//String fireStatus = "";

const char *ssid = "SMV Network ";
const char *password = "hmax8875";



NetworkServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid,password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();

  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(sensor);
  value = map(value,0,4095,0,100);
  value = (value - 100)* -1;
  Serial.print("Hydration : ");
  Serial.println(value);
  delay(100);

  String path = "/Hydration";
  String strHytro = String(value);
  Firebase.setString(path,strHytro);
}

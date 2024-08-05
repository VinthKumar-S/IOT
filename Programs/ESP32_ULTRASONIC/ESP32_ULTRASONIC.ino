#include <WiFi.h>
#include <WiFiClient.h>
#include <IOXhop_FirebaseESP32.h>

#define FIREBASE_HOST "esp32-test-8eea4-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "W7MeD1nAYqeDiBgfnNVRcZIiSVJNydh4RcmcLH6L"

int trigPin = 5;
int echoPin =18;
int distance;
int duration;

//String fireStatus = "";

const char *ssid = "SMV Network ";
const char *password = "hmax8875";



NetworkServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);

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
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin,HIGH);
  distance=duration*0.034/2;
  
  Serial.println(distance);
  delay(100);

  String path = "/ultraSonic/"+String(millis());
  String strDistance = String(distance);
  Firebase.setString(path,strDistance);
}

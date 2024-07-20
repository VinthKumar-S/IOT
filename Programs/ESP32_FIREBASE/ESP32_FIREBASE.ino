#include <WiFi.h>                                                // esp32 library
#include <WiFiClient.h>

#include <IOXhop_FirebaseESP32.h>                                             // firebase library

#define FIREBASE_HOST "esp32-test-8eea4-default-rtdb.firebaseio.com"                         // the project name address from firebase id

#define FIREBASE_AUTH "W7MeD1nAYqeDiBgfnNVRcZIiSVJNydh4RcmcLH6L"                    // the secret key generated from firebase

#define WIFI_SSID "SMV Network"                                          // input your home or public wifi name

#define WIFI_PASSWORD "hmax8875"                                    //password of wifi ssid

String fireStatus = "";                                                     // led status received from firebase

int led = 2;  

const char *ssid = "SMV Network ";
const char *password = "hmax8875";

NetworkServer server(80);
                                                          

void setup() {

  Serial.begin(115200);

  delay(1000);

  pinMode(2, OUTPUT);                


  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
                                                     //print local IP address
  server.begin();
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // connect to firebase

  Firebase.setString("LED_STATUS", "OFF");                                          //send initial string of led status

}

void loop() {
  
  fireStatus = Firebase.getString("LED_STATUS");                     // get led status input from firebase

  if (fireStatus == "ON") {                         // compare the input of led status received from firebase

    Serial.println("Led Turned ON");                 

    digitalWrite(2, HIGH);                                                         // make output led ON

  }

  else if (fireStatus == "OFF") {              // compare the input of led status received from firebase

    Serial.println("Led Turned OFF");

    digitalWrite(2, LOW);                                                         // make output led OFF

  }

  else {

    Serial.println("Wrong Credential! Please send ON/OFF");

  }

}

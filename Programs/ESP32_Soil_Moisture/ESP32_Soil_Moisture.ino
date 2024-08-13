#include <WiFi.h>
#include <WiFiClient.h>
#include <IOXhop_FirebaseESP32.h>
#include <DHT.h>
#define sensor 33
#define relay 4
#define FIREBASE_HOST "esp32-test-8eea4-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "W7MeD1nAYqeDiBgfnNVRcZIiSVJNydh4RcmcLH6L"

DHT dht(26,DHT11);

String fireStatus = "";

const char *ssid = "SMV Network ";
const char *password = "hmax8875";



NetworkServer server(80);

void setup() {
  // wifi code
  Serial.begin(115200);
  WiFi.begin(ssid,password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  //firebase
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  //relay output
  pinMode(relay,OUTPUT);
  digitalWrite(relay,HIGH);
  //temperature sensor
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  setHydration();
  getMotorStatus();
  temperatureLevel();
  delay(100);
}

void setHydration(){
  
  int value = analogRead(sensor);
  value = map(value,0,4095,0,100);
  value = (value - 100)* -1;
  Serial.println("Hydration : ");
  Serial.println(value);
  

  String path = "/Hydration";
  String strHytro = String(value);
  Firebase.setString(path,strHytro);
}

void getMotorStatus(){
  fireStatus = Firebase.getString("Motor");
  if(fireStatus == "ON"){
    Serial.println("Motor On");
    digitalWrite(relay,LOW);
  }
  else if(fireStatus == "OFF"){
    Serial.println("Motor OFF");
    digitalWrite(relay,HIGH);
  } 
}

void temperatureLevel(){
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  Serial.println("Temp: ");
  Serial.println(temp);
  Serial.print("C");
  Serial.println("Humidity: ");
  Serial.println(humidity);
  Serial.print("%");
  delay(2000);
}

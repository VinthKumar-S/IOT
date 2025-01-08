#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
//#include <WiFiClientSecure.h>
//#include <AsyncMqttClient.h>


const char *ssid = "SMV Network ";
const char *password = "hmax8875";

//const char* mqttServer = "c3bd32745792416a9930ecc733eff6c7.s1.eu.hivemq.cloud";
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char* mqttUser = "Vinithkumar";
const char* mqttPassword = "Vini2002";

const char* publish_topic = "esp32/test";

//AsyncMqttClient mqttClient;
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mqttClient.setServer(mqttServer,mqttPort);

}

void reconnect(){
    while(!mqttClient.connected()){
    Serial.println("Connecting to Mqtt Broker..");
    if(mqttClient.connect("ESP32Client",mqttUser,mqttPassword)){
      Serial.println("Connected to MQTT Broker.");
    }
    else{
      Serial.print("Failed, rc=");
      delay(5000);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!mqttClient.connected()){
    reconnect();
  }
  mqttClient.loop();

  static unsigned long lastPublishTime = 0;
  if(millis() - lastPublishTime > 5000){
    lastPublishTime = millis();
    String message = "heloo from esp32";
    mqttClient.publish(publish_topic,message.c_str());
    Serial.print("Published: ");
    Serial.println(message);
  }
}

#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <AsyncMqttClient.h>


const char *ssid = "SMV Network ";
const char *password = "hmax8875";

const char* mqttServer = "c3bd32745792416a9930ecc733eff6c7.s1.eu.hivemq.cloud";
const int mqttPort = 8000;
const char* mqttUser = "Vinithkumar";
const char* mqttPassword = "Vini2002";

AsyncMqttClient mqttClient;

void onMqttConnect(bool sessionPresent){
  Serial.println("Connected to HiveMQ");
  mqttClient.subscribe("test/topic", 0);
 // publishMessage();
}

void onMqttMessage(char* topic,char* payload,AsyncMqttClientMessageProperties properties,size_t len,size_t index,size_t total){
  Serial.printf("Received message on topic %s: %s\n",topic,payload);
}

void publishMessage(){
  Serial.println("Publish message ");

  String payload = "Hello from esp32";

  mqttClient.publish("test/topic", 0,false,payload.c_str());
}

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
  // mqttClient.connect();

  mqttClient.setServer(mqttServer,mqttPort);
  mqttClient.setCredentials(mqttUser,mqttPassword);
  mqttClient.onConnect(onMqttConnect);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.connect();
  

}

// void onMqttConnect(/*bool sessionPresent*/){
//   Serial.println("Connected to MQTT.");

//   mqttClient.publish("testTopic",0,false,"Hello from ESP32");
  
//   mqttClient.subscribe("testTopic", 0);
// }

// void onMqttMessage(char* topic,char* payload,AsyncMqttClientMessageProperties properties,size_t size,size_t index,size_t total){
//   Serial.printf("Message received: %s: %s\n",topic,payload);
// }

void loop() {
  publishMessage();
  delay(1000);
}

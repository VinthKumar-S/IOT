#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char *ssid = "SMV Network ";
const char *password = "hmax8875";
const char* mqttServer ="broker.hivemq.com";
const int mqttPort = 1883;
const char* mqttTopic = "test/json";

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic,byte* payload,unsigned int length){
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);

  String message;
  for(int i=0;i<length;i++){
    message +=(char)payload[i];
  }
  Serial.println("Received message: "+message);

  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc,message);
  if(!error){
    const char* command = doc["command"];
    Serial.println("Command: "+String(command));
  }
  else{
    Serial.println("Failed to parse JSON");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  // put your setup code here, to run once:

  client.setServer(mqttServer,mqttPort);
  client.setCallback(callback);

  while(!client.connected()){
    Serial.println("Connecting to Mqtt...");
    if(client.connect("ESP32Client")){
      Serial.println("Connected to Mqtt");
      client.subscribe(mqttTopic);
    }
    else{
      Serial.print("Failed with state");
      Serial.println(client.state());
      delay(2000);
    }
  }

  StaticJsonDocument<200> doc;
  doc["temperature"] = 25.5;
  doc["humidity"]=60;

  char jsonBuffer[200];
  serializeJson(doc,jsonBuffer);
  client.publish(mqttTopic,jsonBuffer);
}

void loop() {
  // put your main code here, to run repeatedly:
  client.loop();
}

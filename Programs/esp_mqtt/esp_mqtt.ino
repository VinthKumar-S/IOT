
#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

const char *ssid = "SMV Network ";
const char *password = "hmax8875";
const char* mqtt_server ="broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

//NetworkServer server(80);

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
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server,1883);
  client.setCallback(/*std::function<void (char *, uint8_t *, unsigned int)> */callback);

  while(!client.connected()){
    if(client.connect("ESP32Client")){
      Serial.println("Connected to MQTT broker");
      client.subscribe("flutter/to/esp32");
    }
    else{
      Serial.print("Failed to connected, rc=");
      Serial.println(client.state());
      Serial.println(client.state());
      delay(2000);
    }
  }
  //server.begin();
}

void callback(char* topic,byte* payload,unsigned int length){
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print("Message: ");

  for(int i=0; i<length;i++){
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void loop() {
  if(!client.connected()){
    setup();
  }
  client.loop();
  client.publish("esp32/to/flutter","Hello from ESP32");
  delay(200);
}

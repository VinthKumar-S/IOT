
#include <WiFi.h>
#define BLYNK_PRINT Serial
#include <WiFiClient.h>

const char *ssid = "SMV Network ";
const char *password = "hmax8875";

NetworkServer server(80);

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

  server.begin();
}

void loop() {

}

#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3rVqmkvpy"
#define BLYNK_TEMPLATE_NAME "LED on and off"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Enter your Auth token
char auth[] = "aOoK8liRazcpWXf-1PC_ZArSPdTQC8l5";

//Enter your WIFI SSID and password
char ssid[] = "SMV Network";
char pass[] = "hmax8875";

void setup(){
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop(){
  Blynk.run();
}

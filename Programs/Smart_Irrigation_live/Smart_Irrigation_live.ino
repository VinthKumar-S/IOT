
//Include the library files
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <WiFi.h>
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3v7OpIRuT"
#define BLYNK_TEMPLATE_NAME "Plant watering system"
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define sensor 33
#define relay 4

LiquidCrystal_I2C lcd(0x27, 16, 2);

BlynkTimer timer;

const char *ssid = "SMV Network ";
const char *password = "hmax8875";
char auth[] = "6D-DYWCVePPCaDfR1iYtGgQcFenjOPJB";

NetworkServer server(80);

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, password, "blynk.cloud", 80);

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

  Serial.begin(115200);
  Blynk.begin(auth, ssid, password, "blynk.cloud", 80);
  lcd.begin();
  lcd.backlight();
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);

  lcd.setCursor(1, 0);
  lcd.print("System Loading");
  for (int a = 0; a <= 15; a++) {
    lcd.setCursor(a, 1);
    lcd.print(".");
    delay(200);
  }
  lcd.clear();
}

void soilMoisture() {
  int value = analogRead(sensor);
  value = map(value, 0, 4095, 0, 100);
  value = (value - 100) * -1;
  Blynk.virtualWrite(V0, value);
  Serial.println(value);
  lcd.setCursor(0, 0);
  lcd.print("Moisture :");
  lcd.print(value);
  lcd.print(" ");
}

//Get the button value
BLYNK_WRITE(V1) {
  bool Relay = param.asInt();
  if (Relay == 1) {
    digitalWrite(relay, LOW);
    delay(200);
    lcd.setCursor(0, 1);
    lcd.print("Motor is ON ");
  } else {
    digitalWrite(relay, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Motor is OFF");
  }
}

void loop() {
  soilMoisture();
  Blynk.run();//Run the Blynk library

}

#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

const char *ssid = "SMV Network ";
const char *password = "hmax8875";
const char* mqttServer = "c3bd32745792416a9930ecc733eff6c7.s1.eu.hivemq.cloud";
//const int mqttPort = 8883;
const char* mqttUser = "Vinithkumar";
const char* mqttPassword = "Vini2002";
const char* ca_cert = \
"-----BEGIN CERTIFICATE-----\n"\
"MIIFCzCCA/OgAwIBAgISA7NXJMeI1If+CSICLyQe6/LYMA0GCSqGSIb3DQEBCwUA\n"\
"MDMxCzAJBgNVBAYTAlVTMRYwFAYDVQQKEw1MZXQncyBFbmNyeXB0MQwwCgYDVQQD\n"\
"EwNSMTEwHhcNMjQxMjIzMjI0OTI0WhcNMjUwMzIzMjI0OTIzWjAfMR0wGwYDVQQD\n"\
"DBQqLnMxLmV1LmhpdmVtcS5jbG91ZDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCC\n"\
"AQoCggEBAKVuz2sMPmxx2w/f81/YAEKTbNZMJPk2+ooLFg5hxXvReF+AwIT4XvZ+\n"\
"MLhSKvFxmghJF+BB9WyhqrcJLGDCP4s6SOLWTYixEoTcaLUviqqn+06kYqDJ6E83\n"\
"NGsc7T42DlPnzqcZZjPRed9rt4CP3RgeZlWyYZgiD8FoJG9gie8ytihF/FkGZT8T\n"\
"N4Vkl2vQa3mfBWeeKrcuhcLPxqIWDz/30iYfLtEe5JYYScoCKTXcP9SUStjpR8pD\n"\
"vfOWdvasOAuBy7yBbx01/4lcQt50hfbhTR/K14/D4rNkuuvU7ktSQnoxVXC8YDwG\n"\
"zkny10DFt65mVYLNZcBQtOLHHOZGV30CAwEAAaOCAiswggInMA4GA1UdDwEB/wQE\n"\
"AwIFoDAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIwDAYDVR0TAQH/BAIw\n"\
"ADAdBgNVHQ4EFgQUgsEjDU35+EWJKBsFxJ0lM0PXMi4wHwYDVR0jBBgwFoAUxc9G\n"\
"pOr0w8B6bJXELbBeki8m47kwVwYIKwYBBQUHAQEESzBJMCIGCCsGAQUFBzABhhZo\n"\
"dHRwOi8vcjExLm8ubGVuY3Iub3JnMCMGCCsGAQUFBzAChhdodHRwOi8vcjExLmku\n"\
"bGVuY3Iub3JnLzAzBgNVHREELDAqghQqLnMxLmV1LmhpdmVtcS5jbG91ZIISczEu\n"\
"ZXUuaGl2ZW1xLmNsb3VkMBMGA1UdIAQMMAowCAYGZ4EMAQIBMIIBAwYKKwYBBAHW\n"\
"eQIEAgSB9ASB8QDvAHYAzPsPaoVxCWX+lZtTzumyfCLphVwNl422qX5UwP5MDbAA\n"\
"AAGT9euKuwAABAMARzBFAiEA7kt5ecRQhyl1JsSPpgt4bN14o+/BZspQCq0d46Wy\n"\
"03wCIDZ17LnI6Hh+cIF6SlX64OB4pc18XilUqI7pffaEJEENAHUAzxFW7tUufK/z\n"\
"h1vZaS6b6RpxZ0qwF+ysAdJbd87MOwgAAAGT9euK3wAABAMARjBEAiAlffjlUAeU\n"\
"7T6o7ISkiFGXz5G9tx2BB2C5f+GQdqc59QIgEdxGXKjoAJYYlYeZqig2LQxxkdPZ\n"\
"JaYjkrdr9PBeVcYwDQYJKoZIhvcNAQELBQADggEBADKUM+E39KujX/GS+beQajyU\n"\
"/19CFjB+TXYoaXpRPbXTL9XvhCNWI5ZiGc+uGOFneNBED+24YoC1JTLW3a+bWfuJ\n"\
"hBl8bjJoxbP38MsffsWnQ3CGEO4EdcwqdyYf68qGY9FhxvVAx7nzf8qGzRuN0waQ\n"\
"INpYn6eTjZiCICHPdnQnntVSfTza+mzNEBYqZpHAqkpUywG8pEUytJG7ECw5Z79r\n"\
"bEo3gwI2XCfSfVS57aizBYWeZq0tvAmfy7YD3ubo/IIjB4WhxINwgVAPk5oqSToM\n"\
"ZzKtyDiKUcubGARwO0QPjufvvvmbKB56xNtKELvpSTOUCrei9HQcV+utJWvrZSA=\n"\
"-----END CERTIFICATE-----\n";

WiFiClientSecure espClient;
PubSubClient client(espClient);

void reconnect(){
  while(!client.connected()){
    Serial.println("Attempting Mqtt connection..");
    if(client.connect("ESP32Client",mqttUser,mqttPassword)){
      Serial.println("connected");
    }else{
      Serial.println("Failed Connection");
      Serial.println(client.state());
      delay(5000);
    }
  }
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

  espClient.setCACert(ca_cert);

  client.setServer(mqttServer,8883);
}

void loop() {
  if(!client.connected()){
    reconnect();
  }
  client.loop();
}

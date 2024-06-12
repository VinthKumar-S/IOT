#define sensorpin A0 // analog pin 0

void setup() {
 Serial.begin(9600);
  
}

void loop() {
int a=analogRead(sensorpin);
Serial.println(a);
delay(500);

}

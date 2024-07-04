void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("MQ135 Library");
}

void loop() {
  // put your main code here, to run repeatedly:
  int raw_data=analogRead(A0);
  Serial.print("Gas Value:");
  Serial.print(raw_data);
  delay(400);
}

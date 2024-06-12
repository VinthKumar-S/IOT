int flux;

void setup() {
  pinMode(6,INPUT);
  Serial.begin(9400);
  // put your setup code here, to run once:

}

void loop() {
  flux=digitalRead(6);
  Serial.println(flux);
  delay(500);
  // put your main code here, to run repeatedly:

}

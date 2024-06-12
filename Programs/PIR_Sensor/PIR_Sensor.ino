void setup() {
  pinMode(3,INPUT);
  pinMode(12,OUTPUT);
  Serial.begin(96000);
  // put your setup code here, to run once:

}

void loop() {
  int pir=digitalRead(3);
  Serial.println(pir);
  delay(500);
  if(pir==1)
  {
    digitalWrite(12,HIGH);    
  }
  else
  {
    digitalWrite(12,LOW);
  }
  // put your main code here, to run repeatedly:

}

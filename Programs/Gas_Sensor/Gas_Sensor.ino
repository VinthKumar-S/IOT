void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);
  pinMode(7,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int gas=analogRead(A0);
  Serial.println(gas);
  delay(500);
  if(gas>=500)
  {
    digitalWrite(7,HIGH);// put your main code here, to run repeatedly:
  }
  else{
    digitalWrite(7,LOW);
  }
}

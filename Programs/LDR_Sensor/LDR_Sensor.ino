void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode(10,OUTPUT);
 pinMode(A0,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int Idr=analogRead(A0);
  Serial.println(Idr);
  if(Idr>=20)
  {
    digitalWrite(10,HIGH);
  }
  else
  {
    digitalWrite(10,LOW);
  }
}

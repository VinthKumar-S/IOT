void setup() {
  Serial.begin(9600);
  pinMode(12,INPUT);
  pinMode(5,OUTPUT);// put your setup code here, to run once:

}

void loop() {
  int IR=digitalRead(12);
  Serial.println(IR);
  if(IR==1)
  {
    digitalWrite(5,HIGH);
  }
  else{
    digitalWrite(5,LOW);
  }
  // put your main code here, to run repeatedly:

}

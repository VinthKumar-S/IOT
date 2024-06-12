
int distance;
int duration;

void setup() {
  pinMode(9,OUTPUT);
  pinMode(10,INPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(9,LOW);
  delay(2);
  
  digitalWrite(9,HIGH);
  delay(10);
  
  digitalWrite(9,LOW);
  duration=pulseIn(10,HIGH);
  Serial.println("Distance");
  distance=duration*0.034/2;
  Serial.println(distance);
  delay(100);

}

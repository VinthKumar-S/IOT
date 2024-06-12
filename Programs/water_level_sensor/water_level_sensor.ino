
int water;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  water=analogRead(A0);
  Serial.println("Please Insert the Sensor");
  delay(200);
  Serial.println(water);
  delay(700);
  
}

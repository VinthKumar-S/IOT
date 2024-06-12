int sen;
float out;

void setup() {
  Serial.begin(9600);
  pinMode(A5,INPUT);
  // put your setup code here, to run once:

}

void loop() {
  sen=analogRead(A5);
  out=sen*0.0048828125;
  Serial.println("Please Insert the Sensor");
  delay(500);
  Serial.println("OUTPUT is");
  Serial.println(out);
  Serial.println("");
  delay(1000);
  // put your main code here, to run repeatedly:

}

const int trig = 11;
const int echo = 12;


int duration = 0;
int distance = 0;


void setup() {
  // put your setup code here, to run once:
    pinMode(trig , OUTPUT);
  pinMode(echo , INPUT);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(trig , HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig , LOW);


  duration = pulseIn(echo , HIGH);
  distance = (duration/2) / 28.5 ;
  Serial.println(distance);
}

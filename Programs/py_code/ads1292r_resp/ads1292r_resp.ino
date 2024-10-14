void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //infectedVal();
  normalVal();
}

void normalVal(){
   for(int i=0; i<360;i++){
    float normalWave = 512+100*sin(i*PI/100);
    Serial.println(normalWave);
    delay(100);
  }
  delay(2000);
}

void infectedVal(){
   for(int i=0; i<360;i++){
    float infectedWave = 512+random(50,150)*sin(i*PI/100);
    Serial.println(infectedWave);
    delay(100);
  }
  delay(2000);
}

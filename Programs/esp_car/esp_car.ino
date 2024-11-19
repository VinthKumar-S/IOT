int motor1Pin1 = 27;
int motor1Pin2 = 26;
int enable1Pin = 14;
int motor2Pin1 = 33;
int motor2Pin2 = 25;
int enable2Pin = 32;

const int freq = 30000;
const int resolution = 8;
int dutyCycle = 180;


const int pwmChannel1 = 0;
const int pwmChannel2 = 1;

void setup(){
  pinMode(motor1Pin1,OUTPUT);
  pinMode(motor1Pin2,OUTPUT);
  pinMode(enable1Pin,OUTPUT);
  pinMode(motor2Pin1,OUTPUT);
  pinMode(motor2Pin2,OUTPUT);
  pinMode(enable2Pin,OUTPUT);


   ledcAttachChannel(enable1Pin,freq,resolution,pwmChannel1);
   ledcAttachChannel(enable2Pin,freq,resolution,pwmChannel2);

   Serial.begin(115200);

   Serial.print("Testing DC Motor...");
   
}

void loop(){

   Serial.println("Moving Forward");
   digitalWrite(motor1Pin1,LOW);
   digitalWrite(motor1Pin2,HIGH);
   digitalWrite(motor2Pin1,LOW);
   digitalWrite(motor2Pin2,HIGH);
   delay(2000);

   Serial.println("Moving Backwards");
   digitalWrite(motor1Pin1,HIGH);
   digitalWrite(motor1Pin2,LOW);
   digitalWrite(motor2Pin1,LOW);
   digitalWrite(motor2Pin2,HIGH);
   delay(2000);

   Serial.println("Motor stopped");
   digitalWrite(motor1Pin1,LOW);
   digitalWrite(motor1Pin2,LOW);
   digitalWrite(motor2Pin1,LOW);
   digitalWrite(motor2Pin2,LOW);
    delay(1000);

   
   digitalWrite(motor1Pin1,HIGH);
   digitalWrite(motor1Pin2,LOW);
   digitalWrite(motor2Pin1,HIGH);
   digitalWrite(motor2Pin2,LOW);
   

   while(dutyCycle <= 255){
      ledcWrite(enable1Pin,dutyCycle);
      ledcWrite(enable2Pin,dutyCycle);
      Serial.print("Forward with duty cycle:");
      Serial.println(dutyCycle);
      dutyCycle = dutyCycle + 5;
      delay(500);   
   }

   dutyCycle = 180;
}

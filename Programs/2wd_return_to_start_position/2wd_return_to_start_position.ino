int motor1Pin1 = 27;
int motor1Pin2 = 26;
int enable1Pin = 14;
int motor2Pin1 = 33;
int motor2Pin2 = 25;
int enable2Pin = 32;

const int freq = 30000;
const int resolution = 8;
int dutyCycle = 180;
int rotateDcycle = 157;

const int pwmChannel1 = 0;
const int pwmChannel2 = 1;

const int stopDuration = 2500;
const int rotateLeftDuration = 1100;
int numOfExecution=2;
int runingCount=0;
int nodeCount=1;



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

  if(numOfExecution==1){
      moveForward(stopDuration);
      delay(stopDuration);
      stopMotors(stopDuration);
      delay(1000);
      rotateRight(stopDuration);
      delay(800);
      moveForward(stopDuration);
  } 
  else if(numOfExecution==2){
      moveForward(stopDuration);
      delay(stopDuration);
      rotateLeft(rotateLeftDuration);
      delay(500);
      stopMotors(stopDuration);
      delay(stopDuration);
     // nodePoints();
      for(runingCount=0;runingCount<2;runingCount++){
       nodePoints(); 
      }
      moveForward(500);
      delay(500);
      rotateLeft(rotateLeftDuration);
      delay(500);
      moveForward(stopDuration);
      delay(stopDuration); 
      rotateLeft(rotateLeftDuration);
      delay(500);
      moveForward(stopDuration);
      delay(stopDuration);
      rotateLeft(rotateLeftDuration);
      delay(500);
      stopMotors(stopDuration);
      delay(stopDuration);

  } 
}

void moveForward(int duration) {
  Serial.println("Move Forward");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  setSpeed(dutyCycle);
  //delay(duration);
  
}

// Function to turn left
void turnLeft(int duration) {
  Serial.println("Turn to Left");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  setSpeed(dutyCycle);
  delay(duration);
}

// Function to turn right
void turnRight(int duration) {
  Serial.println("Turn to Right");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  setSpeed(dutyCycle);
  //delay(duration);
}

void rotateRight(int duration){
  Serial.println("Rotate Right");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  setSpeed(rotateDcycle);
  delay(duration);
}

void rotateLeft(int duration){
  Serial.println("Rotate Left");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  setSpeed(rotateDcycle);
  delay(duration);
}

// Function to stop the motors
void stopMotors(int duration) {
  Serial.println("Motor Stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  setSpeed(0);
  delay(duration);
}

void nodePoints(){
  Serial.print("Node : ");
  Serial.println(runingCount);
  moveForward(1000);
  delay(1000);
  stopMotors(stopDuration);
  delay(stopDuration);
}

// Function to set motor speed
void setSpeed(int speed) {
  ledcWrite(enable1Pin,speed);
  ledcWrite(enable2Pin,speed);
}
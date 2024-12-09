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

const int stopDuration = 2000;

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
  Serial.println("Moving to Destination 1...");
  moveForward(2000); // Move forward for 2 seconds
  stopMotors();

  //delay(stopDuration); // Pause at the destination

  // Move to the second destination (turn left)
  Serial.println("Turning to Destination 2...");
  turnLeft(1000); // Turn left for 1 second
  moveForward(2000); // Move forward for 2 seconds
  stopMotors();

  //delay(stopDuration); // Pause at the destination

  // Move to the third destination (turn right)
  Serial.println("Turning to Destination 3...");
  turnRight(1000); // Turn right for 1 second
  moveForward(2000); // Move forward for 2 seconds
  stopMotors();

  //delay(stopDuration); // Pause at the destination

  // End of semi-circular path
  Serial.println("Path Complete. Restarting...");
 // delay(5000);

}

void moveForward(int duration) {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  setSpeed(dutyCycle);
  delay(duration);
}

// Function to turn left
void turnLeft(int duration) {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  setSpeed(dutyCycle);
  delay(duration);
}

// Function to turn right
void turnRight(int duration) {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  setSpeed(dutyCycle);
  delay(duration);
}

// Function to stop the motors
void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  setSpeed(0);
}

// Function to set motor speed
void setSpeed(int speed) {
  ledcWrite(enable1Pin,speed);
  ledcWrite(enable2Pin,speed);
}
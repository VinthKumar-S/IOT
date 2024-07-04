#define ECHOpin 5 // it defines the ECHO pin of the sensor to pin 5 of Arduino  
#define TRIGpin 6  
#include <Servo.h> 
// we have defined the variable  
long duration; // variable for the duration of sound wave travel  
int distance; // variable for the distance measurement  

Servo myservo;   

int pos = 0;

int cm = 0;

void setup()   
{  
  pinMode(TRIGpin, OUTPUT); // It sets the ECHO pin as OUTPUT  
  pinMode(ECHOpin, INPUT); // It sets the TRIG pin as INPUT  
  Serial.begin(9600); // // Serial Communication at the rate of 9600 bps  
  Serial.println("Test of the Ultrasonic Sensor HC-SR04"); // It will appear on Serial Monitor  
  Serial.println("with the Arduino UNO R3 board"); 

  digitalWrite(12,LOW);
  myservo.attach(9); 
}  
void loop()   
{  
  // It first sets the TRIG pin at LOW for 2 microseconds  
  digitalWrite(TRIGpin, LOW);  
  delayMicroseconds(4);  
  // It now sets TRIG pin at HIGH for 15 microseconds  
  digitalWrite(TRIGpin, HIGH);  
  delayMicroseconds(15);  
  digitalWrite(TRIGpin, LOW);  
  // It will read the ECHO pin and will return the time   
  duration = pulseIn(ECHOpin, HIGH);  
  // distance formula  
  distance = duration*(0.034/2); // (speed in microseconds)  
  // Speed of sound wave (340 m/s)divided by 2 (forward and backward bounce)  
  // To display the distance on Serial Monitor  
  Serial.print("Distance: ");  
  Serial.print(distance);  
  Serial.println(" cm");
  
  if(distance<30){

   for (pos = 90; pos >= 0; pos -= 1) { 
    myservo.write(pos);
    delay(15);                                     
  }
   Serial.print("Open..");
   delay(3000);
   
   if(distance<30)
   {
    Serial.print("Open..");
   }
   else
   {
    for (pos = 0; pos <= 70; pos += 1) { 
          myservo.write(pos);             
          delay(15);                       
    }
    Serial.print("Close..");
   }
    delay(15); 
  } 
  delay(10);//specified unit of distance  
}  

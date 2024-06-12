#include<Servo.h>//need library for this
Servo Myservo;
int pos;
void setup()
{
Myservo.attach(9);//servo motor digtal pin
}

void loop()
{
  
  
for(pos=0;pos<=180;pos++){//can change degree here
Myservo.write(pos);
delay(15);//speed of rotation
}
  delay(1000);
  
  for(pos=180;pos>=0;pos--){
Myservo.write(pos);
delay(15);
}
  delay(1000);
  
}

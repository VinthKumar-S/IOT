int count=0;
char c;
String id;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  Serial.println("Please scan your RFID TAG");

  

}

void loop() {
  // put your main code here, to run repeatedly:
 // Serial.print("Enter here");
  c= Serial.read();
  count++;

  id +=c;
 // Serial.println(count);
  
  while(Serial.available()>0)
  {
    //Serial.println(count);  
  if(count==12)
  {
    Serial.print(id);
    if(id=="AB123456789A")
    {
      Serial.println("Valid TAG");
      digitalWrite(13,HIGH);
    }
    else
    {
      digitalWrite(13,LOW);
      Serial.println("Invalid TAG");
    }
  }
  }
  count=0;
  id="";
  delay(500);

}

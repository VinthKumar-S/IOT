/* Code By Satyam Singh , Subscribe youtube channel Now */

#define sensorpin A0 // analog pin 0

#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(5, 0);
    lcd.print("FORCE");
    lcd.setCursor(3, 1);
    lcd.print("DETECTOR");
    delay(1000);
    lcd.clear();
  

}

void loop() {
  int force=analogRead(sensorpin);
  int force_per= map(force, 0, 205, 0, 100);
  lcd.setCursor(4,0);
  lcd.print("FORCE (%)");
  lcd.setCursor(7,1);
  lcd.print(force_per);
  delay(500);
  lcd.clear();
  

}

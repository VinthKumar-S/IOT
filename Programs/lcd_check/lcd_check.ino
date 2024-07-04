#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Initialize the LCD
// Set the I2C address (usually 0x27) and the dimensions (16 columns and 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Initialize the LCD
  lcd.init();
  lcd.backlight();  // Turn on the backlight

  // Display a welcome message
  lcd.setCursor(0, 0);  // Set the cursor to column 0, row 0
  lcd.print("Hello, World!");  // Print a message

  lcd.setCursor(0, 1);  // Set the cursor to column 0, row 1
  lcd.print("Counter: 0");  // Print the initial counter value
}

void loop() {
  static int counter = 0;  // Initialize a counter

  // Update the counter every second
  delay(1000);
  ++counter;

  // Update the counter display
  lcd.setCursor(9, 1);  // Set the cursor to column 9, row 1
  lcd.print(counter);  // Print the counter value
}

#include <SPI.h>

// Pin definitions for MAX30001 TinyECG
#define CS_PIN 10       // Chip Select for SPI
#define DRDY_PIN 8      // Data Ready pin
#define START_PIN 9     // Start pin
#define RESET_PIN 7     // Reset pin

// Function prototypes
void initMAX30001();
uint32_t readECGData();

void setup() {
  // Initialize Serial for output
  Serial.begin(9600);

  // Initialize SPI communication
  SPI.begin();

  // Set up pin modes
  pinMode(CS_PIN, OUTPUT);
  pinMode(DRDY_PIN, INPUT);
  pinMode(START_PIN, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);

  // Reset MAX30001
  digitalWrite(RESET_PIN, LOW);
  delay(100);
  digitalWrite(RESET_PIN, HIGH);

  // Initialize MAX30001 settings
  initMAX30001();

  // Start data acquisition
  digitalWrite(START_PIN, HIGH);
}

void loop() {
  // Check if data is ready (DRDY pin goes low)
  if (digitalRead(DRDY_PIN) == LOW) {
    uint32_t ecgData = readECGData();  // Read ECG data from MAX30001
    Serial.print("ECG Data: ");
    Serial.println(ecgData);
  }
}

// Function to initialize the MAX30001 sensor
void initMAX30001() {
  // Begin communication with MAX30001
  digitalWrite(CS_PIN, LOW);
  
  // Configure MAX30001 registers
  // Example: Configuring the ECG control register
  SPI.transfer(0x10);    // Address of ECG control register
  SPI.transfer(0x00);    // Send data to initialize (refer to the datasheet for actual values)
  
  // Example: Configure bioimpedance (respiration)
  SPI.transfer(0x12);    // Address for bioimpedance control register
  SPI.transfer(0x00);    // Send appropriate value to initialize
  
  // End communication
  digitalWrite(CS_PIN, HIGH);
}

// Function to read ECG data from MAX30001
uint32_t readECGData() {
  uint32_t ecgValue = 0;

  // Begin communication with MAX30001
  digitalWrite(CS_PIN, LOW);
  
  // Read ECG data (24 bits, 3 bytes)
  SPI.transfer(0x01); // Command to read ECG data register (replace with actual command)
  ecgValue = SPI.transfer(0x00);         // First byte
  ecgValue = (ecgValue << 8) | SPI.transfer(0x00);  // Second byte
  ecgValue = (ecgValue << 8) | SPI.transfer(0x00);  // Third byte
  
  // End communication
  digitalWrite(CS_PIN, HIGH);
  
  return ecgValue;
}

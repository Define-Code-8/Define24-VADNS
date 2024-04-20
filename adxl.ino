#include <Wire.h>

const int MPU_addr = 0x68; // MPU-6050 I2C address

int16_t AcX, AcY, AcZ; // Variables to store raw acceleration data

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // Set to zero to wake up the MPU-6050
  Wire.endTransmission(true);

  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); // Starting register for accelerometer data
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 6, true); // Request 6 bytes of accelerometer data

  // Read accelerometer data
  AcX = Wire.read() << 8 | Wire.read(); // Combine high and low bytes
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();

  // Print raw acceleration data
  Serial.print("AcX = ");
  Serial.print(AcX);
  Serial.print(" | AcY = ");
  Serial.print(AcY);
  Serial.print(" | AcZ = ");
  Serial.println(AcZ);

  delay(100); // Add a delay to avoid overwhelming the serial monitor
}
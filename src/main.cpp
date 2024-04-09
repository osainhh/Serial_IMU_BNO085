#include <Arduino.h>
#include <BNO080.h>
#include <quat.h>
#include <Wire.h>

#define BNO_ADDRESS 0x4a
#define PIN_IMU_SDA D4
#define PIN_IMU_SCL D5
#define I2C_SPEED 400000

BNO080 imu;

void setup() {
  Serial.begin(115200);

  delay(2000);

  Serial.println();
  Serial.println("BNO085 Test");

  // For some unknown reason the I2C seem to be open on ESP32-C3 by default. Let's just close it before opening it again. (The ESP32-C3 only has 1 I2C.)
  Wire.end(); 

  Wire.flush();
  Wire.begin(static_cast<int>(PIN_IMU_SDA), static_cast<int>(PIN_IMU_SCL));
  imu.begin(BNO_ADDRESS, Wire);
  Wire.setTimeOut(150);
  Wire.setClock(I2C_SPEED);
  delay(500);

  imu.enableRotationVector(50);

  Serial.println("Rotation vector enabled");
  Serial.println("Output in form i, j, k, real, accuracy");
}

void loop() {
  Quat nRotation;
  uint8_t calibrationAccuracy;
  if (imu.dataAvailable() == true) {
    float quatI = imu.getQuatI();
    float quatJ = imu.getQuatJ();
    float quatK = imu.getQuatK();
    float quatReal = imu.getQuatReal();
    float quatRadianAccuracy = imu.getQuatRadianAccuracy();
    imu.getGameQuat(nRotation.x, nRotation.y, nRotation.z, nRotation.w, calibrationAccuracy);
  
    Serial.print(nRotation.x, 2);
    Serial.print(",");
    Serial.print(nRotation.y, 2);
    Serial.print(",");
    Serial.print(nRotation.z, 2);
    Serial.print(",");
    Serial.print(nRotation.w, 2);
    Serial.print(",");
    Serial.print(calibrationAccuracy, 2);
    Serial.print(",");
    Serial.println();
  }
}

#include <Arduino.h>
#include <BNO080.h>
#include <quat.h>
#include <Wire.h>
#include "sensor/sensor.h"

Sensor::Sensor sensor;

void setup() {
  Serial.begin(115200);

  delay(2000);

  Serial.println();
  Serial.println("BNO085 Test");

  sensor.setup();
}

void loop() {
  sensor.update();
}

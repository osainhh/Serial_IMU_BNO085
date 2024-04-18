#include <Arduino.h>
#include <BNO080.h>
#include <quat.h>
#include <Wire.h>
#include "sensor/sensor.h"
#include "serial/serial.h"
#include "led/led.h"

Sensor::Sensor sensor;

void setup() {
  LED::setup();
  Serial.begin(115200);
  
  delay(2000);
  Command::setUp();

  Serial.println();
  //Serial.println("BNO085 Test");

  sensor.setup();
}

void loop() {
  sensor.update();
  Command::Update();
}

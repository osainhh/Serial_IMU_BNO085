#include <Arduino.h>
#include "led.h"

namespace LED {
    void setup() {
        pinMode(LED_PIN, OUTPUT);
    }

    void led_on() {
        digitalWrite(LED_PIN, HIGH);
    }

    void led_off() {
        digitalWrite(LED_PIN, LOW);
    }
}
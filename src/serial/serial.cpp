#include "serial.h"
#include <CmdCallback.hpp>
#include "sensor/sensor.h"

namespace Command {
    Sensor::Sensor sensor;
    CmdCallback<6> cmdCallbacks;
    CmdParser cmdParser;
    CmdBuffer<256> cmdBuffer;
    
    void cmdReboot(CmdParser * parser) {
        Serial.println("REBOOT");
        ESP.restart();
    }

    void setUp() {
        //cmdCallbacks.addCmd("REBOOT", &cmdReboot);
    }

    void update() {
        //cmdCallbacks.updateCmdProcessing(&cmdParser, &cmdBuffer, &Serial);
    }
}
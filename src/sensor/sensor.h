#include <Arduino.h>
#include <Wire.h>
#include <BNO080.h>

#define BNO_ADDRESS 0x4a
#define PIN_IMU_SDA D4
#define PIN_IMU_SCL D5
#define I2C_SPEED 400000

struct sGyro {
    float x;
    float y;
    float z;
};

struct sAccel {
    float x;
    float y;
    float z;
};

struct sMag {
    float x;
    float y;
    float z;
};

namespace Sensor {
    class Sensor {
        public:

            void setup();
            void update();
        private:
            BNO080 imu;
            sGyro gyro;
            sAccel accel;
            sMag mag;
            void sendData_Serial(sGyro g, sAccel a, sMag m);
            void calibrate();
            void getGyro(sGyro *g);
            void getAccel(sAccel *a);
            void getMag(sMag *m);
    };
};
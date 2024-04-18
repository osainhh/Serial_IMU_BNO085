#include <Arduino.h>
#include <Wire.h>
#include <BNO080.h>

#define BNO_ADDRESS 0x4a
#define PIN_IMU_SDA D4
#define PIN_IMU_SCL D5
#define I2C_SPEED 400000

struct sRot {
    float i;
    float j;
    float k;
    float r;
    byte acc;
};

struct sGyro {
    float x;
    float y;
    float z;
    byte acc;
};

struct sAccel {
    float x;
    float y;
    float z;
    byte acc;
};

struct sMag {
    float x;
    float y;
    float z;
    byte acc;
};

struct sAng {
    float roll;
    float pitch;
    float yaw;
};

namespace Sensor {
    class Sensor {
        public:
            void setup();
            void update();

        private:
            BNO080 imu;
            sRot rot;
            sGyro gyro;
            sAccel accel;
            sMag mag;
            sAng angle;
            uint8_t data;
            String ds;
            void sendData_Serial(sRot r, sGyro g, sAccel a, sMag m, sAng ang);
            void getRot(sRot *r);
            void getGyro(sGyro *g);
            void getAccel(sAccel *a);
            void getMag(sMag *m);
            void getAngle(sAng *ang);
            void sensor_enable();
    };
};
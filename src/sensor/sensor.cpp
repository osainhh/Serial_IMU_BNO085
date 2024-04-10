#include "sensor.h"

namespace Sensor {
    void Sensor::sendData_Serial(sGyro g, sAccel a, sMag m) {
        // Gyro
        Serial.print(g.x, 2);
        Serial.print(",");
        Serial.print(g.y,2);
        Serial.print(",");
        Serial.print(g.z, 2);
        Serial.print(",");

        // Acc
        Serial.print(a.x, 2);
        Serial.print(",");
        Serial.print(a.y,2);
        Serial.print(",");
        Serial.print(a.z, 2);
        Serial.print(",");

        // Mag
        Serial.print(m.x, 2);
        Serial.print(",");
        Serial.print(m.y,2);
        Serial.print(",");
        Serial.print(m.z, 2);

        Serial.println();
    }

    void Sensor::getGyro(sGyro *g) {
        g->x = imu.getGyroX();
        g->y = imu.getGyroY();
        g->z = imu.getGyroZ();
    }

    void Sensor::getAccel(sAccel *a) {
        a->x = imu.getLinAccelX();
        a->y = imu.getLinAccelY();
        a->z = imu.getLinAccelZ();
    }

    void Sensor::getMag(sMag *m) {
        m->x = imu.getMagX();
        m->y = imu.getMagY();
        m->z = imu.getMagZ();
    }

    void Sensor::setup() {
        Wire.end(); 

        Wire.flush();
        Wire.begin(static_cast<int>(PIN_IMU_SDA), static_cast<int>(PIN_IMU_SCL));
        imu.begin(BNO_ADDRESS, Wire);
        Wire.setTimeOut(150);
        Wire.setClock(I2C_SPEED);
        delay(500);

        imu.enableGyro(50);
        imu.enableLinearAccelerometer(50);
        imu.enableMagnetometer(50);

        Serial.println("Rotation vector enabled");

    }

    void Sensor::update() {
        if (imu.dataAvailable() == true) {
            getGyro(&gyro);
            getAccel(&accel);
            getMag(&mag);
            sendData_Serial(gyro, accel, mag);
        }
    }
}

#include "sensor.h"

namespace Sensor {
    void printAccuracyLevel(byte acc) {
        if (acc == 0) Serial.print(F("Unreliable"));
        else if (acc == 1) Serial.print(F("LOW"));
        else if (acc == 2) Serial.print(F("Medium"));
        else if (acc == 3) Serial.print(F("HIGH"));
    }
    void Sensor::sendData_Serial(sRot r, sGyro g, sAccel a, sMag m) {
        // Rot Quat
        Serial.print(r.i, 2);
        Serial.print(F(","));
        Serial.print(r.j,2);
        Serial.print(F(","));
        Serial.print(r.k, 2);
        Serial.print(F(","));
        printAccuracyLevel(r.acc);
        Serial.print(F(","));
        
        // Gyro
        Serial.print(g.x, 2);
        Serial.print(F(","));
        Serial.print(g.y,2);
        Serial.print(F(","));
        Serial.print(g.z, 2);
        Serial.print(F(","));
        printAccuracyLevel(g.acc);
        Serial.print(F(","));

        // Acc
        Serial.print(a.x, 2);
        Serial.print(F(","));
        Serial.print(a.y,2);
        Serial.print(F(","));
        Serial.print(a.z, 2);
        Serial.print(F(","));
        printAccuracyLevel(a.acc);
        Serial.print(F(","));

        // Mag
        Serial.print(m.x, 2);
        Serial.print(F(","));
        Serial.print(m.y,2);
        Serial.print(F(","));
        Serial.print(m.z, 2);
        Serial.print(F(","));
        printAccuracyLevel(m.acc);

        Serial.println();
    }

    void Sensor::getRot(sRot *r) {
        r->i = imu.getQuatI();
        r->j = imu.getQuatJ();
        r->k = imu.getQuatK();
        r->r = imu.getQuatReal();
        r->acc = imu.getQuatAccuracy();
    }

    void Sensor::getGyro(sGyro *g) {
        g->x = imu.getGyroX();
        g->y = imu.getGyroY();
        g->z = imu.getGyroZ();
        g->acc = imu.getGyroAccuracy();
    }

    void Sensor::getAccel(sAccel *a) {
        a->x = imu.getLinAccelX();
        a->y = imu.getLinAccelY();
        a->z = imu.getLinAccelZ();
        a->acc = imu.getLinAccelAccuracy();
    }

    void Sensor::getMag(sMag *m) {
        m->x = imu.getMagX();
        m->y = imu.getMagY();
        m->z = imu.getMagZ();
        m->acc = imu.getMagAccuracy();
    }

    void Sensor::setup() {
        Wire.end(); 

        Wire.flush();
        Wire.begin(static_cast<int>(PIN_IMU_SDA), static_cast<int>(PIN_IMU_SCL));
        imu.begin(BNO_ADDRESS, Wire);
        Wire.setTimeOut(150);
        Wire.setClock(I2C_SPEED);
        delay(500);

        imu.enableRotationVector(50);
        imu.enableGyro(50);
        imu.enableLinearAccelerometer(50);
        imu.enableMagnetometer(50);

        imu.calibrateAll();
        Serial.println(F("BNO085 Ready"));

    }

    void Sensor::update() {
        if (imu.dataAvailable() == true) {
            getRot(&rot);
            getGyro(&gyro);
            getAccel(&accel);
            getMag(&mag);
            sendData_Serial(rot, gyro, accel, mag);
        }
    }
}

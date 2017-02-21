#ifndef COMPASS_H
#define COMPASS_H

#include <Arduino.h>
#include <I2C.h>
#include <Vector3D.h>
#include <MadgwickAHRS.h>

#define MPU9250_ADDRESS 0x68
#define MAG_ADDRESS 0x0C

#define GYRO_FULL_SCALE_250_DPS 0x00
#define GYRO_FULL_SCALE_500_DPS 0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18

#define ACC_FULL_SCALE_2_G 0x00
#define ACC_FULL_SCALE_4_G 0x08
#define ACC_FULL_SCALE_8_G 0x10
#define ACC_FULL_SCALE_16_G 0x18

typedef struct CompassData {
    int pitch;
    int roll;
    int yaw;
} CompassData;

class Compass {
public:
    Compass() {};
    void init();

    Vector3D readAccelerometer();
    Vector3D readGyroscope();
    Vector3D readMagnetometer();

    CompassData pitchRollYaw();

private:
    Madgwick filter;

    float convertRawAcceleration(int raw){
        // Since we are using 2G range
        // -2g maps to a raw value of -32768
        // +2g maps to a raw value of 32767

        float a = (raw * 2.0) / 32768.0;
        return a;
    }

    float convertRawGyro(int raw) {
        // Since we are using 500 degrees/seconds range
        // -500 maps to a raw value of -32768
        // +500 maps to a raw value of 32767

        float g = (raw * 500.0) / 32768.0;
        return g;
    }
};

#endif

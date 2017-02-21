#ifndef Compass_h
#define Compass_h

#include <Arduino.h> //AR
//#include <Motor.h> //Motor Lib
#include <Light.h> //Light Sensor Lib
#include <Madgwick.h> //converting pitch, roll and yaw into a heading (Cheers old m8 Madgwick for developing a mad alogrithm)
#include <Vector3D.h> //Just a struct
#include <Wire.h> //Arduino Wire
#include <Math.h> //Mathsssss

#define COMPASS_ADDRESS 0x68 //I2C Address for Compass
#define MAG_ADDRESS 0x0C //I2C Address for Magnetometer

#define GYRO_FULL_SCALE_250_DPS 0x00 //Data to write to the module to midify settings, DPS = Degrees Per Second
#define GYRO_FULL_SCALE_500_DPS 0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18

#define ACC_FULL_SCALE_2_G 0x00 //Same thing as above for Accel
#define ACC_FULL_SCALE_4_G 0x08
#define ACC_FULL_SCALE_8_G 0x10
#define ACC_FULL_SCALE_16_G 0x18

typedef struct CompassData { //Struct that contains the pitch, roll and yaw from the gyro
    int pitch;
    int roll;
    int yaw;
}CompassData;

class Compass{ //Main class

public:
    Compass(){}; //Init Function
    void start(); //Start Function that isnt even used as it is only used for updating settings that are stated above
    double doubleMod(double value, double maxValue); //Yep ignore this, doesnt work anyway
    double calcHeading(double heading); //Used to calc the heading you are at

    Vector3D calcAccel(); //some class inits
    Vector3D calcGyro();
    Vector3D calcMag();

    CompassData pitchRollYaw();

private:
    Madgwick filter; //The filter used to convert pitch roll and yaw into a heading


    void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data); //Just a standard I2C read function
    void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data); //Standard I2C Write Function

    float convertRawAccel(int raw){ //converts raw accel
        float a = (raw * 2.0) / 32768.0;
        return a;
    }

    float convertRawGyro(int raw){ //converts raw gyro
        float g = (raw * 250.0) / 32768.0;
        return g;
    }

};

#endif

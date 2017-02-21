#ifndef LightController_h
#define LightController_h

#include <Arduino.h>
//#include <Motor.h>
#include <Compass.h>

class LightController{

public:
    LightController(int front, int back, int left, int right, int F_threshold, int B_threshold, int L_threshold, int R_threshold);
    void calibrateLight(int pin);
    void calcMultiplier(double runHeading);
private:
    int Sensors[4] = {};
    int currentReading;
    int Thresholds[4] = {};

    int FrontS, BackS, LeftS, RightS, Front_T, Back_T, Left_T, Right_T;

    int moveAngles[4][4] = {
        {255, 208, -208, -255},
        {-255, -208, 208, 255},
        {180, -255, -255, 180},
        {-180, 255, 255, -180}
    };
};

#endif

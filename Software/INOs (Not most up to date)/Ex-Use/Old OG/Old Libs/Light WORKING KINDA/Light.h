#ifndef LIGHT_H
#define LIGHT_H

#include "arduino.h"

class light{

public:
    light() {}
    float warning45(int desiredSensor);
    float warningInt = 1;
private:
    int WhiteThresholdLeft = 50;
    int WhiteThresholdRight = 50;
    int WhiteThresholdFront = 50;
    int WhiteThresholdBack = 50;

    int moveArray[21][4] = {
    {0,0,0,0},
    {-100, -82, 82, 100},
    {-68, -91, 46, 100},
    {-41, -99, 16, 100},
    {-11, -100, -16, 92},
    {23, -100, -51, 83},
    {71, -100, -100, 71},
    {83, -51, -100, 23},
    {92, -16, -100, -11},
    {100, 16, -99, -41},
    {100, 46, -91, -68},
    {100, 82, -82, -100},
    {68, 91, -46, -100},
    {41, 99, -16, -100},
    {11, 100, 16, -92},
    {-23, 100, 51, -83},
    {-71, 100, 100, -71},
    {-83, 51, 100, -23},
    {-92, 16, 100, 11},
    {-100, -16, 99, 41},
    {-100, -46, 91, 68}
    };
    float lightMultiply1 = 0.5;
    float lightMultiply2 = 0.2;
    float lightMultiply3 = -0.4;
    float lightMultiply4 = -0.7;

    int leftData[4] = {};
    int rightData[4] = {};
    int frontData[4] = {};
    int backData[4] = {};

    int Left[4] = {};
    int Right[4] = {};
    int Front[4] = {};
    int Back[4] = {};
    int finalLightData[16] = {};
    int modifiedLightArray[16] = {};

    int bestSensor = 0;
    int lightSide = 0;

    #define LeftLight1Pin 1
    #define LeftLight2Pin 2
    #define LeftLight3Pin 3
    #define LeftLight4Pin 4
    #define RightLight1Pin 5
    #define RightLight2Pin 6
    #define RightLight3Pin 7
    #define RightLight4Pin 8
    #define FrontLight1Pin 9
    #define FrontLight2Pin 10
    #define FrontLight3Pin 11
    #define FrontLight4Pin 12
    #define BackLight1Pin 13
    #define BackLight2Pin 14
    #define BackLight3Pin 15
    #define BackLight4Pin 16
};



#endif

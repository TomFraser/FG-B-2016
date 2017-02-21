#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>

class light{ //Main Light Object Class

public:
    light(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int pin7, int pin8, int pin9, int pin10, int pin11, int pin12, int pin13, int pin14, int pin15, int pin16, bool isGoing); //Light init function used in making the object
    float warning45(int warningTSOP, int maxVal[16]); //The function used for determining if we are crossing a white line and the danger (warning) level
    //void read(int warningTSOP); //this isnt even used I dont think, it is left over from some origional code I wrote ages ago, ignore please

private: //some defines along with the moveArray for when using static motor values (for noobs) (like us :P)
    int LeftLight1Pin, LeftLight2Pin, LeftLight3Pin, LeftLight4Pin, RightLight1Pin, RightLight2Pin, RightLight3Pin, RightLight4Pin,
        BackLight1Pin, BackLight2Pin, BackLight3Pin, BackLight4Pin, FrontLight1Pin, FrontLight2Pin, FrontLight3Pin, FrontLight4Pin;
    int warningTSOP;

    int frontThresholds[4];
    int rightThresholds[4];
    int leftThresholds[4];
    int backThresholds[4];

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
    float warningInt = 10;

    int bestSensor = 0;
    int lightSide = 0;

};

#endif

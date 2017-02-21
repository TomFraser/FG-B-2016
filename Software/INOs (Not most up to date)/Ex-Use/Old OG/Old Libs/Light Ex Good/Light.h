#ifndef LIGHT_H
#define LIGHT_H

#include "Arduino.h"

class light{

public:
    light(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int pin7, int pin8, int pin9, int pin10, int pin11, int pin12, int pin13, int pin14, int pin15, int pin16);
    float warning45(int warningTSOP);
    void read(int warningTSOP);

private:
    int LeftLight1Pin, LeftLight2Pin, LeftLight3Pin, LeftLight4Pin, RightLight1Pin, RightLight2Pin, RightLight3Pin, RightLight4Pin,
        BackLight1Pin, BackLight2Pin, BackLight3Pin, BackLight4Pin, FrontLight1Pin, FrontLight2Pin, FrontLight3Pin, FrontLight4Pin;
    int warningTSOP;

    int WhiteThresholdLeft = 50;
    int WhiteThresholdRight = 50;
    int WhiteThresholdFront = 50;
    int WhiteThresholdBack = 50;

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

    int lightSide = 0;

};

#endif

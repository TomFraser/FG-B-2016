#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>

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

class light {
public:
    light();
    float warning45(int warningTSOP);
    int bestSensor;
};

#endif

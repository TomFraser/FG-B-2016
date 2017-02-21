#ifndef LIGHTNEW_H
#define LIGHTNEW_H

#include "Arduino.h"

class light{
public:
    light();
    float warning45(int warningTSOP);
    int bestSensor;
private:
    int lightPin1,lightPin2;
};

#endif

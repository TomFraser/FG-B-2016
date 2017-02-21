#ifndef LIGHT_H
#define LIGHT_H

#include "arduino.h"

class light{

public:
    light(int input) {}
    float warning45(int bestSensor);


private:
    int bestSensor;
};



#endif

#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include <Arduino.h>

class LightSensor {
public:
    LightSensor() {}
    LightSensor(int in, int threshold);

    int read();
    bool isOnWhite();

private:
    int inPin;
    int thresholdValue;
};

#endif

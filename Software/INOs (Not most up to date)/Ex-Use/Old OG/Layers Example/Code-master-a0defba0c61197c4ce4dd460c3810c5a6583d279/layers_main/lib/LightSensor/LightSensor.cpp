#include "LightSensor.h"

LightSensor::LightSensor(int in, int threshold) {
    inPin = in;
    thresholdValue = threshold;

    pinMode(in, INPUT);
}

int LightSensor::read() {
    return analogRead(inPin);
}

bool LightSensor::isOnWhite() {
    if (read() > thresholdValue) {
        return true;
    } else {
        return false;
    }
}

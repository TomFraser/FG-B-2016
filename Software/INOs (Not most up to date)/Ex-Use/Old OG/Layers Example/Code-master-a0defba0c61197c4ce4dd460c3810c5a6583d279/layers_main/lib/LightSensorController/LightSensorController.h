#ifndef LIGHTSENSORCONTROLLER_H
#define LIGHTSENSORCONTROLLER_H

#include <Arduino.h>
#include <LightSensor.h>
#include <LineLocation.h>
#include <Pins.h>

class LightSensorController {
public:
    LightSensorController();

    LineLocation readLineLocation();

private:
    LightSensor lsLeftOuter;
    LightSensor lsLeftInner;
    LightSensor lsFrontOuter;
    LightSensor lsFrontInner;
    LightSensor lsRightOuter;
    LightSensor lsRightInner;
    LightSensor lsBackLeft;
    LightSensor lsBackRight;
};

#endif

#ifndef new_light_h
#define new_light_h

#include <Arduino.h>

class new_light{

private:
    void calibrate();
    void getReady();
    void sensorGrouping();

    int readings[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    enum arms{
        left,
        right,
        back,
        front
    };

public:
    new_light(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int pin7, int pin8, int pin9, int pin10, int pin11, int pin12, int pin13, int pin14, int pin15, int pin16);
    void calculateArms(int bestTSOP, bool pixy, bool compass, int heading);
    void calculateIndiv(int bestTSOP, bool pixy, bool compass, int heading);

};

#endif

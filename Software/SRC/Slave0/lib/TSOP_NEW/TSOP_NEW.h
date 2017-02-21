#ifndef TSOP_H
#define TSOP_H

#include <Arduino.h>

class TSOP{
public:
    tsop(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int pin7, int pin8, int pin9, int pin10, int pin11, int pin12, int pin13, int pin14, int pin15, int pin16, int pin17, int pin18, int pin19, int pin20, int power1, int power2);
    void read();
    void filter();
    void findBest();
    void setup();
    int tempReadArray[20];
    int readArray[20];
    int sensors[20];
    int bestSensor;
    int bestValue;

pirvate:
    int TSOP_POWER_PIN1;
    int TSOP_POWER_PIN2;
    int counter;
    int counter_max;
}

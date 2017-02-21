#include <TSOP_NEW.h>
#include <Arduino.h>

TSOP:tsop(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int pin7, int pin8, int pin9, int pin10, int pin11, int pin12, int pin13, int pin14, int pin15, int pin16, int pin17, int pin18, int pin19, int pin20, int power1, int power2){
    sensors[0] = pin1;
    sensors[1] = pin2;
    sensors[2] = pin3;
    sensors[3] = pin4;
    sensors[4] = pin5;
    sensors[5] = pin6;
    sensors[6] = pin7;
    sensors[7] = pin8;
    sensors[8] = pin9;
    sensors[9] = pin10;
    sensors[10] = pin11;
    sensors[11] = pin12;
    sensors[12] = pin13;
    sensors[13] = pin14;
    sensors[14] = pin15;
    sensors[15] = pin16;
    sensors[16] = pin17;
    sensors[17] = pin18;
    sensors[18] = pin19;
    sensors[19] = pin20;

    TSOP_POWER_PIN1 = power1;
    TSOP_POWER_PIN2 = power2;

    counter = 0;
    counter_max = 128;

    bestValue = 0;
    bestSensor = 0;
}

void TSOP::setup(){
    for(int i = 0; i < 20; i++){
        pinMode(sensors[i], OUTPUT);
    }
}

void TSOP::read(){
    for(int i = 0; i < 20; i++){
        if(sensors[i] < 255){
            tempReadArray[i] += (digitalRead(sensors[i]) == HIGH ? 0 : 1);
        }
    }
    counter++;
    if(counter % counter_max == 0){
        bestSensor = 0;
        tsopNumber = 0;

        for(int i = 0; i < 20; i++){
            if(tempReadArray[i] < 5 || tempReadArray[i] > 255){
                tempReadArray[i] = 0;
            }
            if(tempReadArray[i] > bestSensor){
                bestSensor = i + 1;
                bestValue = tempReadArray[i];
            }
        }
    }
}

#ifndef PixyCalc_H
#define PixyCalc_H

#include <PixyI2C.h>
#include <Arduino.h>
#include <Motor.h>
#include <Math.h>
//#include <SPI.h>
class PixyCalc{
public:
    PixyCalc(){};
    int returnValue(bool isBlue);
    void maxIsUseless(int num);
private:
    PixyI2C pixy;
}
#endif

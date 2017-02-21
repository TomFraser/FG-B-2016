#ifndef PixyCalc_H
#define PixyCalc_H

#include <Pixy.h>
#include <Arduino.h>
#include <Motor.h>
#include <Math.h>
#include <SPI.h>
#include <PixyNull.h>

class PixyCalc{
public:
    PixyCalc() = {};
    PixyNull returnValue(bool isBlue);
    void maxIsUseless(int num);
private:
    Pixy pixy;
}
#endif

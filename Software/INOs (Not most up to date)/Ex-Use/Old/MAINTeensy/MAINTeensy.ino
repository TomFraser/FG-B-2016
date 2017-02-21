#include <Pixy.h>
#include <Defines.h>
#include <[TOUCH SCREEN LIBRARY HERE]>
#include <SPI.h>
#include <SPI4teensy3>

Pixy pixy;

void setup(){
    Serial.begin(115200);
    pixy.init();

}

void loop(){
    pixy.getBlocks();

}

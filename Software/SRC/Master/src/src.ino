//Coded with <3 by Thomas Fraser
#include <t3spi.h>
//#include <EEPROM.h>
#include <PixyI2C.h>
//#include <PixyCalc.h>
//#include <useEEPROM.h>

#define dataLength 1

#define SS_TSOP 10

#define pixyCentreX 160

PixyI2C pixy;

volatile uint16_t dataOut[dataLength] = {};
volatile uint16_t dataIn[dataLength] = {};
int finalVal = 0;

int eeprom_count = 0;

T3SPI MASTER_TEENSY;
//useEEPROM EEPROM_USE = useEEPROM(1.00, 1, 0, 0, 1, 1, 0, 1, 0, 0); //float speed, int tsops, int pixy, int ultrasonics, int compass, int light, int xbee, int orbit int angle, int goal

//PixyI2C pixy;

void setup(){
    pinMode(13, OUTPUT);
    pinMode(10, OUTPUT); //SS to Slave0 (TSOP)
    pinMode(20, OUTPUT); //SS to Slave1 (MOTORS)
    Serial.begin(9600);
    MASTER_TEENSY.begin_MASTER(ALT_SCK, MOSI, MISO, CS1, CS_ActiveLOW);
    MASTER_TEENSY.setCTAR(CTAR_0, 16, SPI_MODE0, LSB_FIRST, SPI_CLOCK_DIV8);
    //pixy.init();
    //EEPROM_USE.updateValues();
    delay(1000);
    digitalWrite(13, HIGH); //Tells us when the teensy is ready. As this is the Master, we have the longest delay on this one, allowing the slaves to init before connection is attempted.
}

void loop(){
    delay(40);
    dataIn[0] = 0;
    MASTER_TEENSY.txrx16(dataOut, dataIn, dataLength, CTAR_0, CS0); //Recieve from TSOP Slave
    finalVal = dataIn[0];
    dataOut[0] = finalVal;
    MASTER_TEENSY.tx16(dataOut, dataLength, CTAR_0, CS1); //Transmit TSOPs to Motor Slave
}

int getPixy(bool blue){
    bool isBlue = blue;
    if(pixy.getBlocks()){
        if(pixy.blocks[0].signature == 1 && (isBlue == true) || pixy.blocks[0].signature == 2 && (isBlue == false)){ //Sig 1 is blue, sig 2 is yellow
            int objectCentreX = pixy.blocks[0].x;
            int objectCentreY = pixy.blocks[0].y;

            if(objectCentreX > pixyCentreX){
                return objectCentreX - pixyCentreX;
            }
            else if(objectCentreX < pixyCentreX){
                return pixyCentreX - objectCentreX;
            }
        }
    }
    else{
        return 0;
    }
}

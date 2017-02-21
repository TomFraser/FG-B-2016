//Coded with <3 by Thomas Fraser
#include <Documents/Developer/SHF GIT/Software/LIBS/t3spi/t3spi.h>
//#include <EEPROM.h>
//#include <Pixy.h>
//#include <useEEPROM.h>

#define dataLength 1

#define SS_TSOP 10

#define pixyCentreX 160

volatile uint16_t dataOut[dataLength] = {};
volatile uint16_t dataIn[dataLength] = {};
int finalVal = 0;

int eeprom_count = 0;

T3SPI MASTER_TEENSY;
//useEEPROM EEPROM_USE = useEEPROM(1.00, 1, 0, 0, 1, 1, 0, 1, 0, 0); //float speed, int tsops, int pixy, int ultrasonics, int compass, int light, int xbee, int orbit int angle, int goal

//Pixy pixy;

void setup(){
    pinMode(13, OUTPUT);
    pinMode(10, OUTPUT); //SS to Slave0 (TSOP)
    pinMode(20, OUTPUT); //SS to Slave1 (MOTORS)
    Serial.begin(9600);
    MASTER_TEENSY.begin_MASTER(ALT_SCK, MOSI, MISO, CS1, CS_ActiveLOW);
    MASTER_TEENSY.setCTAR(CTAR_0, 16, SPI_MODE0, LSB_FIRST, SPI_CLOCK_DIV8);
    //pixy.init();
    //EEPROM_USE.updateValues();
    delay(5000);
    digitalWrite(13, HIGH); //Tells us when the teensy is ready. As this is the Master, we have the longest delay on this one, allowing the slaves to init before connection is attempted.
}

void loop(){
    delay(2);
    dataIn[0] = 0;
    MASTER_TEENSY.txrx16(dataOut, dataIn, dataLength, CTAR_0, CS0); //Recieve from TSOP Slave
    finalVal = dataIn[0];
    dataOut[0] = finalVal;
    MASTER_TEENSY.tx16(dataOut, dataLength, CTAR_0, CS1); //Transmit TSOPs to Motor Slave
    //EEPROM_COUNTER();
}

/*int getPixy(bool blue){
    bool isBlue = blue;
    if(pixy.getBlocks()){
        if(pixy.blocks[0].signature == 1 && (isBlue == true) || pixy.blocks[0].signature == 2 && (isBlue == false)){
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
}*/

void maxIsUseless(long num){
    long count = num;
    for(long i = 0; i < count; i++){
        Serial.println("Max is Useless");
    }
}
/*
void EEPROM_COUNTER(){
    if(eeprom_count >= 100){
        EEPROM_USE.updateEEPROM();
        eeprom_count = 0;
    }
    else{
        eeprom_count = eeprom_count + 1;
    }
}*/
#include <t3spi.h>

#define dataLength 1

#define SS_TSOP 10
#define SS_MOTOR 600//fix

volatile uint8_t dataOut[dataLength] = {};
volatile uint8_t dataIn[dataLength] = {};
int endMe = 0;

T3SPI MASTER_TEENSY;

void setup(){
  pinMode(10, OUTPUT);//SS to Slave0 (TSOP)
  pinMode(20, OUTPUT);//SS to Slave1 (MOTORS)
    Serial.begin(9600);
    MASTER_TEENSY.begin_MASTER(ALT_SCK, MOSI, MISO, CS1, CS_ActiveLOW);
    MASTER_TEENSY.setCTAR(CTAR_0, 8, SPI_MODE0, LSB_FIRST, SPI_CLOCK_DIV8);
    delay(1000);
}

void loop(){
    dataIn[0] = 0;
    MASTER_TEENSY.txrx8(dataOut, dataIn, dataLength, CTAR_0, CS0);
    endMe = dataIn[0];
    Serial.println(endMe);
    Serial.println(endMe/2);
    Serial.println("");
    Serial.println("");
    dataOut[0] = endMe;
    MASTER_TEENSY.tx8(dataOut, dataLength, CTAR_0, CS1);
    //delay(1000);
}

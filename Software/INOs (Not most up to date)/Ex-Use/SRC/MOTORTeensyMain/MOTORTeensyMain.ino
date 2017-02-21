#include <t3spi.h>
#include <Light.h>
#include <Motor.h>

T3SPI MOTOR_SLAVE;

#define dataLength 1

volatile uint8_t dataIn[dataLength] = {};

int bestSensor = 0; //This must be replaced by pulling the best sensor that was determined by the tsop teensy.
int orbit[21] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};  //Not correct orbit
light lightArray = light(100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115); //Fix with light pins
int returnHomeCounter = 0;

int moveArray[21][4] = {
    {0,0,0,0},
    {-255, -208, 208, 255},
    {-174, -232, 118, 255},
    {-104, -253, 40, 255},
    {-27, -255, -40, 236},
    {60, -255, -130, 213},
    {180, -255, -255, 180},
    {213, -130, -255, 60},
    {236, -40, -255, -27},
    {255, 40, -253, -104},
    {255, 118, -232, -174},
    {255, 208, -208, -255},
    {174, 232, -118, -255},
    {104, 253, -40, -255},
    {27, 255, 40, -236},
    {-60, 255, 130, -213},
    {-180, 255, 255, -180},
    {-213, 130, 255, -60},
    {-236, 40, 255, 27},
    {-255, -40, 253, 104},
    {-255, -118, 232, 174}
};  //Correct Move Array, For 4 Motors

Motor motorD(6, 24, 25, 33, 0, 1);
Motor motorA(5, 8, 9, 32, 0, 1);
Motor motorB(3, 0, 1, 30, 0, 1);   //PWM, IN1, In2, SB, Ignore, Rev
Motor motorC(4, 2, 7, 31, 0, 1);

void setup(){
    Serial.begin(9600);
    MOTOR_SLAVE.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);
    MOTOR_SLAVE.setCTAR_SLAVE(8, SPI_MODE0);

    NVIC_ENABLE_IRQ(IRQ_SPI0);
}

void loop(){
    Motor(bestSensor/2);
    //motorA.set(180);
    //motorB.set(-255);
    //motorC.set(-255);
    //motorD.set(180);

}

void spi0_isr(void){
    MOTOR_SLAVE.rx8(dataIn, dataLength);
    bestSensor = dataIn[0];
    Serial.println(bestSensor/2);
    if(bestSensor == 0){
        bestSensor = -1;
    }
    //Serial.println(recieveData[0]);
}

void Motor(int row) {
    motorA.set(int(moveArray[orbit[row]][0]));//*lightArray.warning45(row));
    motorB.set(int(moveArray[orbit[row]][1]));//*lightArray.warning45(row));
    motorC.set(int(moveArray[orbit[row]][2]));//*lightArray.warning45(row));
    motorD.set(int(moveArray[orbit[row]][3]));//*lightArray.warning45(row));
}

void returnHome(){  //Check rear IR for distance before centering in field and reverting until goal found
}

void runLoop(){
    if(returnHomeCounter != 400){
        if(bestSensor == -1){
            returnHomeCounter++;
        }
        else{
            Motor(bestSensor);
            returnHomeCounter = 0;
        }
    }
    else{
        returnHome();
    }
}

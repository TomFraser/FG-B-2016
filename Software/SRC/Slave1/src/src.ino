//Coded with <3 by Thomas Fraser
#include <t3spi.h>
#include <Light.h>
#include <Motor_old.h>
#include <Motor.h>
#include <Compass.h>
#include <Wire.h>
#include <Math.h>
#include <LightController.h>
//#include <defines.h>
#include <PixyI2C.h>

#define MOTOR_TEST false
#define DEBUG false

int moveArray[21][4] = { //Clockwise
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
};

PixyI2C pixy;

T3SPI MOTOR_SLAVE;

Compass compass;

int threshold[3];

LightController lightArrayNew = LightController(A1, A14, A8, A11, 35, 35, 35, 35);

light lightArray = light(A6, A10, A10, A10, A10, A12, A10, A10, A10, A10, A15, A10, A10, A1, A10, A10, true); //Left Right Back Front 4 of each
//int thresholds[16] = {analogRead(A6), 1000, 1000, 1000, 1000, analogRead(A12), 1000, 1000, 1000, 1000, analogRead(A15), 1000, 1000, analogRead(A1), 1000};

Motor_old motorD(6, 24, 33, 1);
Motor_old motorA(5, 8, 32, 1);
Motor_old motorB(3, 0, 30, 1);
Motor_old motorC(4, 2, 31, 1);

//OG MOTOR PINS
// Motor motorD(6, 24, 25, 33, 0, 1); //PWM, IN1, IN2, SB, Ignore, Rev
// Motor motorA(5, 8, 9, 32, 0, 1);
// Motor motorB(3, 0, 1, 30, 0, 1);
// Motor motorC(4, 2, 7, 31, 0, 1);

#define dataLength 1
#define SPI_COUNTER_MAX 2

#define angToRad 0.01745329251
#define radToAng 57.2957795131

volatile uint16_t dataIn[dataLength] = {};

long previousTime;
double heading;

int bestSensor = 0;
int pixyMove = 0;
//int orbit[21] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}; //Orbit around ball
int orbit[21] = {0,1,7,6,8,9,10,11,11,12,13,7,7,13,15,16,16,14,13,15,1}; //Move Directly to Ball
//int orbit[21] = {0,1,1,8,9,10,10,11,11,12,13,7,7,13,15,14,14,13,12,17,1}; //Move Directly to Ball

int lightSensors[16] = {A6, A7, A8, A9, A13, A12, A11, A10, A17, A16 /*This should be A16 but its broken so we will just use A17 instead.*/, A15, A14, A0, A1, A2, A3}; //Left Right Back Front 4 of each


/*--------------------------------------------------------------------------------------------------------------*/

void spi0_isr(void){ //SPI Trigger
    MOTOR_SLAVE.rx16(dataIn, dataLength);
    bestSensor = dataIn[0];
}

void Motor(int row){
    // motorA.set(int((moveArrayAllinAll[calcMotorArray()][orbit[row]][0]) + compass.calcHeading(heading))/2);
    // motorB.set(int((moveArrayAllinAll[calcMotorArray()][orbit[row]][1]) + compass.calcHeading(heading))/2);
    // motorC.set(int((moveArrayAllinAll[calcMotorArray()][orbit[row]][2]) + compass.calcHeading(heading))/2);
    // motorD.set(int((moveArrayAllinAll[calcMotorArray()][orbit[row]][3]) + compass.calcHeading(heading))/2);

    // motorA.set(-255);
    // motorB.set(-255);
    // motorC.set(-255);
    // motorD.set(-255);

    if(row == 0 || row == 1 || row == 2 || row == 19 || row == 18){
        motorA.set((-255) + (compass.calcHeading(heading))*2);
        motorB.set((-208) + (compass.calcHeading(heading))*2);
        motorC.set((208) + (compass.calcHeading(heading))*2);
        motorD.set((255) + (compass.calcHeading(heading))*2);
    }
    // else if(row == 18){ //    {-180, 255, 255, -180},
    //     motorA.set((int)(-180)*0.2 + compass.calcHeading(heading)*0.2);
    //     motorB.set((int)(255)*0.2 + compass.calcHeading(heading)*0.2);
    //     motorC.set((int)(255)*0.2 + compass.calcHeading(heading)*0.2);
    //     motorD.set((int)(-180)*0.2 + compass.calcHeading(heading)*0.2);
    // }
    // else if(row == 2){
    //     motorA.set((int)(180)*0.2 + compass.calcHeading(heading)*0.2);
    //     motorB.set((int)(-255)*0.2 + compass.calcHeading(heading)*0.2);
    //     motorC.set((int)(-255)*0.2 + compass.calcHeading(heading)*0.2);
    //     motorD.set((int)(180)*0.2 + compass.calcHeading(heading)*0.2);
    // }
    else{
        int getMotorsWhite = calcMotorArray();
        if(getMotorsWhite == 0){
            motorA.set(int((moveArray[orbit[row]][0]) + compass.calcHeading(heading)));
            motorB.set(int((moveArray[orbit[row]][1]) + compass.calcHeading(heading)));
            motorC.set(int((moveArray[orbit[row]][2]) + compass.calcHeading(heading)));
            motorD.set(int((moveArray[orbit[row]][3]) + compass.calcHeading(heading)));
        }
        // if(getMotorsWhite == 1){ //{-180, 255, 255, -180},
        //     for(int i = 0; i < 1200; i++){
        //         motorA.set((-180)*0.5 + compass.calcHeading(heading)*0.25);
        //         motorB.set((255)*0.5 + compass.calcHeading(heading)*0.25);
        //         motorC.set((255)*0.5 + compass.calcHeading(heading)*0.25);
        //         motorD.set((-180)*0.5 + compass.calcHeading(heading)*0.25);
        //     }
        // }
        // else if(getMotorsWhite == 2){ //{180, -255, -255, 180},
        //     for(int i = 0; i < 1200; i++){
        //         motorA.set((180)*0.25 + compass.calcHeading(heading));
        //         motorB.set((-255)*0.25 + compass.calcHeading(heading));
        //         motorC.set((-255)*0.25 + compass.calcHeading(heading));
        //         motorD.set((180)*0.25 + compass.calcHeading(heading));
        //     }
        // }
    }
    // motorA.set(int(moveArray[orbit[row]][0]) + compass.calcHeading(pixyCompass(heading)));
    // motorB.set(int(moveArray[orbit[row]][1]) + compass.calcHeading(pixyCompass(heading)));
    // motorC.set(int(moveArray[orbit[row]][2]) + compass.calcHeading(pixyCompass(heading)));
    // motorD.set(int(moveArray[orbit[row]][3]) + compass.calcHeading(pixyCompass(heading)));

}

void MotorRun(int row){
    if(row <= 10 && row != 1){
        row = row - 5;
    }
    else if(row >= 11 && row != 1){
        row = row + 5;
    }
    motorA.set(int((moveArray[row][0]) + compass.calcHeading(heading))*0.7);
    motorB.set(int((moveArray[row][2]) + compass.calcHeading(heading))*0.7);
    motorC.set(int((moveArray[row][3]) + compass.calcHeading(heading))*0.7);
    motorD.set(int((moveArray[row][4]) + compass.calcHeading(heading))*0.7);
}

void compassData(){
    double reading = (double)compass.calcGyro().z;
    long currentTime = micros();
    heading += (((double)(currentTime - previousTime) / 1000000.0) * reading);
    heading = compass.doubleMod(heading, 360.0);
    previousTime = currentTime;
}

int calcCompass_Pixy(){
    if(compass.calcHeading(heading) >= 225 || compass.calcHeading(heading) <= 135){
        return compass.calcHeading(heading);
    }
    else{
        if(pixyMove != 0){
            return pixyMove;
        }
    }
}

void moveOnAngle(int in1, int in2){ //angle, headingToMove || Sets motor values based on an angle
    int angle = in1;
    int headingToMove = in2;

    int speed = 255;
    int angleArray[4] = {60, 135, 225, 300};

    double returnValues[4] = {};
        returnValues[0] = cos(((angleArray[0] + 90) * angToRad) - (angle * angToRad));
        returnValues[1] = cos(((angleArray[1] + 90) * angToRad) - (angle * angToRad));
        returnValues[2] = cos(((angleArray[2] + 90) * angToRad) - (angle * angToRad));
        returnValues[3] = cos(((angleArray[3] + 90) * angToRad) - (angle * angToRad));

    int angleRad = angle * angToRad;

    double modifiedSpeed = speed / doubleAbs(max(max(max(doubleAbs(returnValues[0]), doubleAbs(returnValues[1])), doubleAbs(returnValues[2])), doubleAbs(returnValues[3])));

    int motor_a_val = (int)(returnValues[0] * modifiedSpeed) + compass.calcHeading(headingToMove);
    int motor_b_val = (int)(returnValues[1] * modifiedSpeed) + compass.calcHeading(headingToMove);
    int motor_c_val = (int)(returnValues[2] * modifiedSpeed) + compass.calcHeading(headingToMove);
    int motor_d_val = (int)(returnValues[3] * modifiedSpeed) + compass.calcHeading(headingToMove);

    motorA.set(motor_a_val); //Needs light stuff multiplier
    motorB.set(motor_b_val);
    motorC.set(motor_c_val);
    motorD.set(motor_d_val);
}

double doubleAbs(double value) {
    if (value > 0) {
        return value;
    } else {
        return -value;
    }
}

void calcLightReadings(){
    for(int i = 0; i < 16; i++){
        Serial.println(analogRead(lightSensors[i]));
    }
    Serial.println("-------------------");
    delay(1000);
}

int calcMotorArray(){
    int readLight[2] = {analogRead(A11), analogRead(A6)};//, analogRead(A16), analogRead(A17)}; //left, right, back, front
    for(int i = 0; i < 2; i++){
        if(readLight[i] >= threshold[i]){
            return i + 1;
        }
        else{
        }
    }
    return 0;
}

int pixyCompass(int headingToMove){
    int pixyCentreX = 160;
    if(pixy.getBlocks()){
        int pixyObjectCentreX = pixy.blocks[0].x;
        if(pixyObjectCentreX > pixyCentreX){
            return headingToMove + ((pixyObjectCentreX - pixyCentreX)/2);
        }
        else if(pixyObjectCentreX < pixyCentreX){
            return headingToMove - ((pixyCentreX - pixyObjectCentreX)/2);
        }
    }
    else{
        return headingToMove;
    }
}


void setup(){
    Wire.begin();
    pinMode(13, OUTPUT);
    Serial.begin(9600);
    MOTOR_SLAVE.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);
    MOTOR_SLAVE.setCTAR_SLAVE(16, SPI_MODE0);

    NVIC_ENABLE_IRQ(IRQ_SPI0);
    digitalWrite(13, HIGH);
    previousTime = micros();

    threshold[0] = analogRead(A11) + 15;
    threshold[1] = analogRead(A6) + 15;
    //threshold[2] = analogRead(A15) + 15;
}

void loop(){
    // #if DEBUG
    // Serial.println(analogRead(A6)); //A6, A12, A16
    // Serial.println(analogRead(A11));
    // Serial.println(analogRead(A16));
    // Serial.println();
    // delay(100);

    //Serial.println(calcMotorArray());
    //calcLightReadings(); //Shows all lightsensor values
    // Serial.println(bestSensor);
    // delay(100);
    compassData();
    Motor(bestSensor);
    //lightArrayNew.calcMultiplier(compass.calcHeading(heading)); //LIGHT SENSORS
}

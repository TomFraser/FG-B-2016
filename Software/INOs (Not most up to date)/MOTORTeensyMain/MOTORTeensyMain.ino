//Coded with <3 by Thomas Fraser
#include <t3spi.h>
#include <Light.h>
#include <Motor.h>
#include <Compass.h>
#include <Wire.h>
#include <Math.h>
//#include <SHFCOMMON.h>

T3SPI MOTOR_SLAVE;

Compass compass;

#define dataLength 1

#define COMPASS_ADDRESS 0x68

#define SPI_COUNTER_MAX 2

#define angToRad 0.01745329251
#define radToAng 57.2957795131

volatile uint16_t dataIn[dataLength] = {};

long previousTime;
double heading;

int bestSensor = 0;
int pixyMove = 0;
//int orbit[21] = {0, 1, 1, 1, 7, 9, 10, 11, 12, 13, 14, 7, 8, 9, 10, 12, 11, 13, 15, 1, 1}; //Orbit around ball
//int orbit[21] = {0, 1, 1, 4, 6, 7, 8, 9, 10, 11, 12, 9, 6, 7, 8, 10, 9, 11, 13, 15, 1}; //Experimental Orbit
int orbit[21] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}; //Move Directly to Ball

int lightSensors[16] = {A6, A7, A8, A9, A13, A12, A11, A10, A17, A17 /*This should be A16 but its broken so we will just use A17 instead.*/, A15, A14, A0, A1, A2, A3};
int thresholds[16] = {};

light lightArray = light(A6, A7, A8, A9, A13, A12, A11, A10, A17, A17 /*This should be A16 but its broken so we will just use A17 instead.*/, A15, A14, A0, A1, A2, A3, true); //Left Right Back Front 4 of each
//light lightArray = light(A9, A8, A7, A6, A10, A11, A12, A13, A14, A15, A16, A17, A0, A1, A2, A3);

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
};

Motor motorD(6, 24, 25, 33, 0, 1); //PWM, IN1, IN2, SB, Ignore, Rev
Motor motorA(5, 8, 9, 32, 0, 1);
Motor motorB(3, 0, 1, 30, 0, 1);
Motor motorC(4, 2, 7, 31, 0, 1);

void setup(){
    Wire.begin();
    pinMode(13, OUTPUT);
    Serial.begin(9600);
    MOTOR_SLAVE.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);
    MOTOR_SLAVE.setCTAR_SLAVE(16, SPI_MODE0);

    NVIC_ENABLE_IRQ(IRQ_SPI0);
    delay(2000);
    digitalWrite(13, HIGH);
    previousTime = micros();
    calcLightReadings(true);
}

void loop(){
    calcLightReadings(true);
    compassData();
    Motor(bestSensor);
    //MotorMove(bestSensor, angle);
    //Serial.println(bestSensor);
}

void spi0_isr(void){ //Wake up in the morning... TRIGGERED [The SPI]
    MOTOR_SLAVE.rx16(dataIn, dataLength);
    bestSensor = dataIn[0];
}

// void MotorMove(int row, int angleIn){
//     int angle = angleIn;
//     motorA.set(int(moveOnAngle(angle, heading, 0))); //Not including Light
//     motorB.set(int(moveOnAngle(angle, heading, 1)));
//     motorC.set(int(moveOnAngle(angle, heading, 2)));
//     motorD.set(int(moveOnAngle(angle, heading, 3)));
// }

void Motor(int row) {
    //float lightSensahs = lightArray.warning45(bestSensor, thresholds);
    //Serial.println(lightSensahs);
    motorA.set(int(moveArray[orbit[row]][0]) + compass.calcHeading(heading)); //* lightSensahs); //Needs Light
    motorB.set(int(moveArray[orbit[row]][1]) + compass.calcHeading(heading)); //* lightSensahs); //Needs Light
    motorC.set(int(moveArray[orbit[row]][2]) + compass.calcHeading(heading)); //* lightSensahs); //Needs Light
    motorD.set(int(moveArray[orbit[row]][3]) + compass.calcHeading(heading)); //* lightSensahs); //Needs Light
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

int moveOnAngle(int in1, int in3, int in2){ //angle, headingToMove, motor (set motor to -1 if you want a motor speed of 0)
    int angle = in1;
    int headingToMove = in3;
    int motor = in2;

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

    switch(motor){
        case -1: return 0; break;
        case 0: return (motor_a_val); break;
        case 1: return (motor_b_val); break;
        case 2: return (motor_c_val); break;
        case 3: return (motor_d_val); break;
    }
}

double doubleAbs(double value) {
    if (value > 0) {
        return value;
    } else {
        return -value;
    }
}

void calcLightReadings(bool doIt){
    bool doLight = doIt;
    int lightReadings[16] = {};
    if(doLight == true){
        //calc Light readings
        for(int i = 0; i < 16; i++){
            lightReadings[i] += analogRead(lightSensors[i]);
            thresholds[i] = lightReadings[i] + 30;
        }
        Serial.println("Done Light Calibration :)");
        for(int i = 0; i < 16; i++){
            Serial.println(lightReadings[i]);
        }
        delay(1000);
    }
    else{
    }
}

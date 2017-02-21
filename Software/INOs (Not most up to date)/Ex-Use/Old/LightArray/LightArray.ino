#include <Light.h>
#include <Motor.h>

int bestSensor = 1; //This must be replaced by pulling the best sensor that was determined by the tsop teensy.
int orbit[21] = {0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10};  //Not correct orbit

light lightArray = light(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);  //Fix with light pins

int moveArray[21][4] = {
    {0,0,0,0},
    {-100, -82, 82, 100},
    {-68, -91, 46, 100},
    {-41, -99, 16, 100},
    {-11, -100, -16, 92},
    {23, -100, -51, 83},
    {71, -100, -100, 71},
    {83, -51, -100, 23},
    {92, -16, -100, -11},
    {100, 16, -99, -41},
    {100, 46, -91, -68},
    {100, 82, -82, -100},
    {68, 91, -46, -100},
    {41, 99, -16, -100},
    {11, 100, 16, -92},
    {-23, 100, 51, -83},
    {-71, 100, 100, -71},
    {-83, 51, 100, -23},
    {-92, 16, 100, 11},
    {-100, -16, 99, 41},
    {-100, -46, 91, 68}
};  //Correct Move Array, For 4 Motors

Motor motorA(3, 0, 1, 30, 0, 0);   //PWM, IN1, In2, SB, Ignore, Rev
Motor motorB(4, 2, 7, 31, 0, 0);
Motor motorC(5, 8, 9, 32, 0, 0);
Motor motorD(6, 24, 25, 33, 0, 0);

void setup(){
    Serial.begin(115200);
}

void loop(){
    Motor(bestSensor);
    Serial.println(moveArray[orbit[bestSensor]][0]*lightArray.warning45(bestSensor));   //Printing Motor Values
}

void Motor(int row) {
    motorA.set(int(moveArray[orbit[row]][0])*lightArray.warning45(row));
    motorB.set(int(moveArray[orbit[row]][1])*lightArray.warning45(row));
    motorC.set(int(moveArray[orbit[row]][2])*lightArray.warning45(row));
    motorD.set(int(moveArray[orbit[row]][3])*lightArray.warning45(row));
}

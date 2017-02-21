#include <Motor.h>
#include <Arduino.h>
#include <Math.h>
#include <Wire.h>

#define COMPASSADDRESS 0x68
#define MAGADDRESS 0x0C
#define GYROCALL 0x18

#define LeftLight1Pin 1
#define LeftLight2Pin 2
#define LeftLight3Pin 3
#define LeftLight4Pin 4
#define RightLight1Pin 5
#define RightLight2Pin 6
#define RightLight3Pin 7
#define RightLight4Pin 8
#define FrontLight1Pin 9
#define FrontLight2Pin 10
#define FrontLight3Pin 11
#define FrontLight4Pin 12
#define BackLight1Pin 13
#define BackLight2Pin 14
#define BackLight3Pin 15
#define BackLight4Pin 16


int IR_SENSOR = 0;
int orbit[] = {};

int8_t compassHome;
int compassCorrect;

int WhiteThresholdLeft = 50;
int WhiteThresholdRight = 50;
int WhiteThresholdFront = 50;
int WhiteThresholdBack = 50;

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
};
float lightMultiply1 = 0.5;
float lightMultiply2 = 0.2;
float lightMultiply3 = -0.4;
float lightMultiply4 = -0.7;

int leftData[4] = {};
int rightData[4] = {};
int frontData[4] = {};
int backData[4] = {};

int Left[4] = {};
int Right[4] = {};
int Front[4] = {};
int Back[4] = {};
int finalLightData[16] = {};
int modifiedLightArray[16] = {};
float warningInt = 1;

int bestSensor = 0;
int lightSide = 0;

Motor motorA(1, 1, 1, 0);
Motor motorB(1, 1, 1, 0);
Motor motorC(1, 1, 1, 0);
Motor motorD(1, 1, 1, 0);

void setup() {
    Serial.begin(115200);
    compassSetup();
}

void loop() {
    compassRead();
    Motor(IR_SENSOR);
}
int warning45(int warningTSOP){
    warningInt = 10;
    lightSide = 0;

    lightRead();

    for(int i = 0; i < 16; i++){
        if(modifiedLightArray[i] >= 1){
                if(i <= 3){
                  lightSide = 1;
                  break;
                }
                else if(i >= 4 && i <= 7){
                  lightSide = 2;
                  break;
                }
                else if(i >= 8 && i <= 11){
                  lightSide = 3;
                  break;
                }
                else if(i >= 12 && i <= 15){
                  lightSide = 4;
                  break;
                }
            }
        }

    if((warningTSOP > 17) || (warningTSOP < 3) && (lightSide == 1)){
        for(int i = 0; i < 4; i++){
            if(modifiedLightArray[i] >= 1){
                switch(i){
                    case 0: warningInt = -8; break;
                    case 1: warningInt = -8; break;
                    case 2: warningInt = -8; break;
                    case 3: warningInt = -8; break;
                }
            }
            if(warningInt == -8){
              break;
            }
        }
    }
    else if(warningTSOP > 2 && warningTSOP < 8 && lightSide == 2){
        for(int i = 4; i < 8; i++){
            if(modifiedLightArray[i] >= 1){
                switch(i){
                    case 4: warningInt = 4; break;
                    case 5: warningInt = 2; break;
                    case 6: warningInt = -4; break;
                    case 7: warningInt = -8; break;
                }
            }
            if(warningInt == -8){
              break;
            }
        }
    }
    else if(warningTSOP > 8 && warningTSOP < 13 && lightSide == 3){
        for(int i = 8; i < 12; i++){
            if(modifiedLightArray[i] >= 1){
                switch(i){
                    case 8: warningInt = 4; break;
                    case 9: warningInt = 2; break;
                    case 10: warningInt = -4; break;
                    case 11: warningInt = -8; break;
                }
            }
            if(warningInt == -8){
              break;
            }
        }
    }
    else if(warningTSOP > 12 && warningTSOP < 18 && lightSide == 4){
        for(int i = 12; i < 16; i++){
            if(modifiedLightArray[i] >= 1){
                switch(i){
                    case 12: warningInt = 4; break;
                    case 13: warningInt = 2; break;
                    case 14: warningInt = -4; break;
                    case 15: warningInt = -8; break;
                }
            }
            if(warningInt == -8){
              break;
            }
        }
    }
  return warningInt/10;
}
void warning42(){
    warningInt = 10;
    lightSide = 0;

    lightRead();

    modifiedLightArray[0] += Front[0];
    modifiedLightArray[1] += Front[1];
    modifiedLightArray[2] += Front[2];
    modifiedLightArray[3] += Front[3];

    modifiedLightArray[4] += Right[0];
    modifiedLightArray[5] += Right[1];
    modifiedLightArray[6] += Right[2];
    modifiedLightArray[7] += Right[3];

    modifiedLightArray[8] += Back[0];
    modifiedLightArray[9] += Back[1];
    modifiedLightArray[10] += Back[2];
    modifiedLightArray[11] += Back[3];

    modifiedLightArray[12] += Left[0];
    modifiedLightArray[13] += Left[1];
    modifiedLightArray[14] += Left[2];
    modifiedLightArray[15] += Left[3];

    for(int i = 0; i < 16; i++){
        if(modifiedLightArray[i] >= 1){
            if(i <= 3){
              lightSide = 1;
              break;
            }
            else if(i >= 4 && i <= 7){
              lightSide = 2;
              break;
            }
            else if(i >= 8 && i <= 11){
              lightSide = 3;
              break;
            }
            else if(i >= 12 && i <= 15){
              lightSide = 4;
              break;
            }
        }
    }
    if(bestSensor > 17 || bestSensor < 3 && lightSide == 1){
        for(int i = 0; i < 4; i++){
            if(modifiedLightArray[i] >= 1){
                switch(i){
                    case 0: warningInt = -8; break;
                    case 1: warningInt = -8; break;
                    case 2: warningInt = -8; break;
                    case 3: warningInt = -8; break;
                }
            }
            if(warningInt == -8){
              break;
            }
        }
    }
    else if(bestSensor > 2 && bestSensor < 8 && lightSide == 2){
        for(int i = 4; i < 8; i++){
            if(modifiedLightArray[i] >= 1){
                switch(i){
                    case 4: warningInt = 4;
                    case 5: warningInt = 2;
                    case 6: warningInt = -4;
                    case 7: warningInt = -8;
                }
            }
            if(warningInt == -8){
              break;
            }
        }
    }
    else if(bestSensor > 8 && bestSensor < 13 && lightSide == 3){
        for(int i = 8; i < 12; i++){
            if(modifiedLightArray[i] >= 1){
                switch(i){
                    case 8: warningInt = 4; Serial.println("Back set to 4");
                    case 9: warningInt = 2; Serial.println("Back set to 2");
                    case 10: warningInt = -4; Serial.println("Back set to -4");
                    case 11: warningInt = -8; Serial.println("Back set to -8");
                }
            }
            if(warningInt == -8){
              break;
            }
        }
    }
    else if(bestSensor > 12 && bestSensor < 18 && lightSide == 4){
        for(int i = 12; i < 16; i++){
            if(modifiedLightArray[i] >= 1){
                switch(i){
                    case 12: warningInt = 4; Serial.println("Left set to 4");
                    case 13: warningInt = 2; Serial.println("Left set to 2");
                    case 14: warningInt = -4; Serial.println("Left set to -4");
                    case 15: warningInt = -8; Serial.println("Left set to -8");
                }
            }
            if(warningInt == -8){
              break;
            }
        }
    }
    return warningInt/10;
}

void lightRead(){
    leftData[0] += digitalRead(LeftLight1Pin);
    leftData[1] += digitalRead(LeftLight2Pin);
    leftData[2] += digitalRead(LeftLight3Pin);
    leftData[3] += digitalRead(LeftLight4Pin);

    rightData[0] += digitalRead(RightLight1Pin);
    rightData[1] += digitalRead(RightLight2Pin);
    rightData[2] += digitalRead(RightLight3Pin);
    rightData[3] += digitalRead(RightLight4Pin);

    frontData[0] += digitalRead(FrontLight1Pin);
    frontData[1] += digitalRead(FrontLight2Pin);
    frontData[2] += digitalRead(FrontLight3Pin);
    frontData[3] += digitalRead(FrontLight4Pin);

    backData[0] += digitalRead(BackLight1Pin);
    backData[1] += digitalRead(BackLight2Pin);
    backData[2] += digitalRead(BackLight3Pin);
    backData[3] += digitalRead(BackLight4Pin);

    for (int i = 0; i < 4; i++) {
        if (leftData[i] > WhiteThresholdLeft) {
            Left[i] = 1;
        } else {
            Left[i] = 0;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (rightData[i] > WhiteThresholdRight) {
            Right[i] = 1;
        } else {
            Right[i] = 0;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (frontData[i] > WhiteThresholdFront) {
            Front[i] = 1;
        } else {
            Front[i] = 0;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (backData[i] > WhiteThresholdBack) {
            Back[i] = 1;
        } else {
            Back[i] = 0;
        }
    }

    finalLightData[0] += Front[0]; // 0-3 contains outer most sensor
    finalLightData[1] += Right[0];
    finalLightData[2] += Back[0];
    finalLightData[3] += Left[0];

    finalLightData[4] += Front[1]; // 4-7 contains 2nd most outer sensor
    finalLightData[5] += Right[1];
    finalLightData[6] += Back[1];
    finalLightData[7] += Left[1];

    finalLightData[8] += Front[2]; // 8-11 contains second closest to the middle of the robot
    finalLightData[9] += Right[2];
    finalLightData[10] += Back[2];
    finalLightData[11] += Left[2];

    finalLightData[12] += Front[3]; // 12-15 contains the closest to the center of the robot
    finalLightData[13] += Right[3];
    finalLightData[14] += Back[3];
    finalLightData[15] += Left[3];
}

float warning() { // int returned will be between 10 and -10 then divided by 10 to get danger float
    warningInt = 10;
    lightSide = 0;

    lightRead();

    for (int i = 0; i < 4; i++) {
        if (finalLightData[i] >= 1) {
            warningInt = 4;
        }
    }
    for (int i = 4; i < 8; i++) {
        if (finalLightData[i] >= 1) {
            warningInt = 2;
        }
    }
    for (int i = 8; i < 12; i++) {
        if (finalLightData[i] >= 1) {
            warningInt = -4;
        }
    }
    for (int i = 12; i < 16; i++) {
        if (finalLightData[i] >= 1) {
            warningInt = -8;
        }
    }
    return warningInt / 10;
}

float warning22() { // int returned will be between 10 and -10 then divided by 10 to get danger float
    warningInt = 10;
    lightSide = 0;
    int modifiedLightArray[16];

    lightRead();

    modifiedLightArray[0] += Front[0];
    modifiedLightArray[1] += Front[1];
    modifiedLightArray[2] += Front[2];
    modifiedLightArray[3] += Front[3];

    modifiedLightArray[4] += Right[0];
    modifiedLightArray[5] += Right[1];
    modifiedLightArray[6] += Right[2];
    modifiedLightArray[7] += Right[3];

    modifiedLightArray[8] += Back[0];
    modifiedLightArray[9] += Back[1];
    modifiedLightArray[10] += Back[2];
    modifiedLightArray[11] += Back[3];

    modifiedLightArray[12] += Left[0];
    modifiedLightArray[13] += Left[1];
    modifiedLightArray[14] += Left[2];
    modifiedLightArray[15] += Left[3];

`   for(int i = 0; i < 16; i++){
        if(modifiedLightArray[i] >= 1){
            switch(i){
                case (i>4):             lightSide = 1;  break;
                case (i<4 && i>8):      lightSide = 2;  break;
                case (i<7 && i>12):     lightSide = 3;  break;
                case (i<11 && i>16):    lightSide = 4;  break;
            }
        }
    }

    if(bestSensor > 17 && bestSensor < 3 && lightSide == 1){
        for(int i = 0; i < 4; i++){
            if(modifiedLightArray[i] >= 1){
                switch(j){
                    case(i == 0): warningInt = 4;
                    case(i == 1): warningInt = 2;
                    case(i == 2): warningInt = -4;
                    case(i == 3): warningInt = -8;
                }
            }
        }
    }
    if(bestSensor > 2 && bestSensor < 8 && lightSide == 2){
        for(int i = 4; i < 8; i++){
            if(modifiedLightArray[i] >= 1){
                switch(i){
                    case(i == 4): warningInt = 4;
                    case(i == 5): warningInt = 2;
                    case(i == 6): warningInt = -4;
                    case(i == 7): warningInt = -8;
                }
            }
        }
    }
    if(bestSensor > 8 && bestSensor < 13 && lightSide == 3){
        for(int i = 8; i < 12; i++){
            if(modifiedLightArray[i] >= 1){
                switch(i){
                    case(i == 8): warningInt = 4;
                    case(i == 9): warningInt = 2;
                    case(i == 10): warningInt = -4;
                    case(i == 11): warningInt = -8;
                }
            }
        }
    }
    if(bestSensor > 12 && bestSensor < 18 && lightSide == 4){
        for(int ji = 12; i < 16; i++){
            if(modifiedLightArray[i] >= 1){
                switch(i){
                    case(i == 12): warningInt = 4;
                    case(i == 13): warningInt = 2;
                    case(i == 14): warningInt = -4;
                    case(i == 15): warningInt = -8;
                }
            }
        }
    return warningInt / 10;
}

void Motor(int row) {
    motorA.set(int(moveArray[orbit[row]][0]));
    motorB.set(int(moveArray[orbit[row]][1]));
    motorC.set(int(moveArray[orbit[row]][2]));
    motorD.set(int(moveArray[orbit[row]][3]));
}

void compassRead(){ // cant be bothered right now.
    int8_t buf[14];
    I2Cread(COMPASSADDRESS, 0x3B, 14, buf);
    int8_t xReading =-(buf[0]<<8 | buf[1]);
    Serial.println(xReading);
    int8_t compassCorrect = xReading - compassHome;
}

int8_t I2Cread(int8_t Address,int8_t Register,int8_t Nbytes,int8_t* Data){
    Wire.beginTransmission(Address);
    Wire.write(Register);
    Wire.endTransmission();

    Wire.requestFrom(Address, Nbytes);
    int8_t index = 0;
    while(Wire.available()){
        Data[index++]=Wire.read();
    }
}

void I2Cwrite(int8_t Address, int8_t Register,int8_t Data){
    Wire.beginTransmission(Address);
    Wire.write(Register);
    Wire.write(Data);
    Wire.endTransmission();
}

void compassSetup(){
    Wire.begin();
    Serial.begin(115200);
    I2Cwrite(COMPASSADDRESS,17, GYROCALL);
    I2Cwrite(MAGADDRESS, 0x0A, 0x01);
    int8_t firstBuf[14];
    I2Cread(COMPASSADDRESS, 0x3B, 14, firstBuf);
    int8_t compassHome =- (firstBuf[0]<<8 | firstBuf[1]);
}

int compassAct(){
    if(compassCorrect >= 180 && compassCorrect <= 359){
        return compassCorrect;
    }
    else if(compassCorrect >= 179 && compassCorrect <= 0)
        return -compassCorrect;
}

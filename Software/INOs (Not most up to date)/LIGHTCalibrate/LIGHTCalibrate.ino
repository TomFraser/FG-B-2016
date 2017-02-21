#include <Light.h>
#include <Thresholds.h>
#include <EEPROM.h>

light lightArray = light(A6, A7, A8, A9, A13, A12, A11, A10, A17, A16, A15, A14, A0, A1, A2, A3); //Left Right Back Front | 4 of each Outtermost going in towards the centre of the robot
int lightSensors[16] = {A6, A7, A8, A9, A13, A12, A11, A10, A17, A16, A15, A14, A0, A1, A2, A3};

int frontAV = 0;
int backAV = 0;
int leftAV = 0;
int rightAV = 0;

int returnReadings[10][16] = {};
int calcAverage = 0;
int finalAverages[16] = {};
int whiteThresholds[16] = {};

void setup(){
    //We don't need to set up anything because the Light library sets the pins provided as inputs. All we need to do is read the sensors and calibrate them.
    //We will calibrate the sensors here and act on it in the loop.
    for(int i = 0; i < 4; i++){
        leftAV += calibrateLightSensors(A6, A7, A8, A9, A13, A12, A11, A10, A17, A16, A15, A14, A0, A1, A2, A3).one;
    }
    leftAV = leftAV / 4;

    for(int i = 0; i < 4; i++){
        rightAV += calibrateLightSensors(A6, A7, A8, A9, A13, A12, A11, A10, A17, A16, A15, A14, A0, A1, A2, A3).two;
    }
    rightAV = rightAV / 4;

    for(int i = 0; i < 4; i++){
        frontAV += calibrateLightSensors(A6, A7, A8, A9, A13, A12, A11, A10, A17, A16, A15, A14, A0, A1, A2, A3).three;
    }
    frontAV = frontAV / 4;

    for(int i = 0; i < 4; i++){
        backAV += calibrateLightSensors(A6, A7, A8, A9, A13, A12, A11, A10, A17, A16, A15, A14, A0, A1, A2, A3).four;
    }
    backAV = backAV / 4;

    EEPROM.update(1, leftAV);
    EEPROM.update(1, rightAV);
    EEPROM.update(1, frontAV);
    EEPROM.update(1, backAV);
}

void loop(){
    //Read the sensors to make sure they are in the right order.
    //Broken Sensors:
    //(A12), (A11), (A16), (A0)

    //Don't do anything in the loop otherwise the eeprom will get overwritten many times
}

Thresholds calibrateLightSensors(int Left1, int Left2, int Left3, int Left4, int Right1, int Right2, int Right3, int Right4, int Back1, int Back2, int Back3, int Back4, int Front1, int Front2, int Front3, int Front4){
    int sensorArray[16] = {Left1, Left2, Left3, Left4, Right1, Right2, Right3, Right4, Back1, Back2, Back3, Back4, Front1, Front2, Front3, Front4};

    //Take a white reading
    for(int j = 0; j < 10; j++){
        for(int i = 0; i < 16; i++){
            returnReadings[j][i] += analogRead(sensorArray[i]);
        }
    }
    for(int z = 0; z < 16; z++){
        for(int i = 0; i < 10; i++){
            int calcAverage = calcAverage + returnReadings[i][z];
        }
        finalAverages[z] += calcAverage / 10;
    }
    for(int i = 0; i < 16; i++){
        whiteThresholds[i] = finalAverages[i] - 50;
    }
    Thresholds whiteReadings = {whiteThresholds[0], whiteThresholds[1], whiteThresholds[2], whiteThresholds[3], whiteThresholds[4], whiteThresholds[5], whiteThresholds[6], whiteThresholds[7], whiteThresholds[8], whiteThresholds[9], whiteThresholds[10], whiteThresholds[11], whiteThresholds[12], whiteThresholds[13], whiteThresholds[14], whiteThresholds[15], };
    return whiteReadings;
}

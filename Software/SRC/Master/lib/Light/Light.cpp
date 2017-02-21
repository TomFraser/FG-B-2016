#include <Light.h>
//#include <EEPROM.h>

light::light(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int pin7, int pin8, int pin9, int pin10, int pin11, int pin12, int pin13, int pin14, int pin15, int pin16, bool isGoing){ //The init function, sets the light sensor pins to inputs

    LeftLight1Pin = pin1;   //left
    LeftLight2Pin = pin2;
    LeftLight3Pin = pin3;
    LeftLight4Pin = pin4;

    RightLight1Pin = pin5; //Right
    RightLight2Pin = pin6;
    RightLight3Pin = pin7;
    RightLight4Pin = pin8;

    BackLight1Pin = pin9; //Back
    BackLight2Pin = pin10;
    BackLight3Pin = pin11;
    BackLight4Pin = pin12;

    FrontLight1Pin = pin13; //Front
    FrontLight2Pin = pin14;
    FrontLight3Pin = pin15;
    FrontLight4Pin = pin16;

    pinMode(LeftLight1Pin, INPUT);
    pinMode(LeftLight2Pin, INPUT);
    pinMode(LeftLight3Pin, INPUT);
    pinMode(LeftLight4Pin, INPUT);

    pinMode(RightLight1Pin, INPUT);
    pinMode(RightLight2Pin, INPUT);
    pinMode(RightLight3Pin, INPUT);
    pinMode(RightLight4Pin, INPUT);

    pinMode(BackLight1Pin, INPUT);
    pinMode(BackLight2Pin, INPUT);
    pinMode(BackLight3Pin, INPUT);
    pinMode(BackLight4Pin, INPUT);

    pinMode(FrontLight1Pin, INPUT);
    pinMode(FrontLight2Pin, INPUT);
    pinMode(FrontLight3Pin, INPUT);
    pinMode(FrontLight4Pin, INPUT);

    //setup light thresholds //some stuff using EEPROM, not sure if we will use this to update the light thresholds everytime we boot or just calibrate once?
    //WhiteThresholdLeft = EEPROM.read(EEPROM_LIGHT_THRESHOLD_ADD_1);
    //WhiteThresholdRight = EEPROM.read(EEPROM_LIGHT_THRESHOLD_ADD_2);
    //WhiteThresholdBack = EEPROM.read(EEPROM_LIGHT_THRESHOLD_ADD_3);
    //WhiteThresholdFront = EEPROM.read(EEPROM_LIGHT_THRESHOLD_ADD_4);
}

float light::warning45(int warningTSOP, int maxVal[16]){ //Pretty much the usefull function that does about everything

    //max goes left, right, back, front
    frontThresholds[0] = maxVal[0];
    frontThresholds[1] = maxVal[1];
    frontThresholds[2] = maxVal[2];
    frontThresholds[3] = maxVal[3];

    rightThresholds[0] = maxVal[4];
    rightThresholds[1] = maxVal[5];
    rightThresholds[2] = maxVal[6];
    rightThresholds[3] = maxVal[7];

    backThresholds[0] = maxVal[8];
    backThresholds[1] = maxVal[9];
    backThresholds[2] = maxVal[10];
    backThresholds[3] = maxVal[11];

    frontThresholds[0] = maxVal[12];
    frontThresholds[1] = maxVal[13];
    frontThresholds[2] = maxVal[14];
    frontThresholds[3] = maxVal[15];

    // for(int i = 0; i < 4; i++){
    //     Serial.println(frontThresholds[i]);
    // }

    //Reset all the arrays and values used kek
    for(int i = 0; i < 4; i++){
        leftData[i] = 0;
        rightData[i] = 0;
        frontData[i] = 0;
        backData[i] = 0;

        Left[i] = 0;
        Right[i] = 0;
        Back[i] = 0;
        Front[i] = 0;
    }
    for(int i = 0; i < 16; i++){
        finalLightData[i] = 0;
    }
    lightSide = 0;
    warningInt = 1.00;
    //Done resetting all the arrays and values used kek

    leftData[0] += analogRead(LeftLight1Pin); //creates an array with all the left side sensors data
    leftData[1] += analogRead(LeftLight2Pin);
    leftData[2] += analogRead(LeftLight3Pin);
    leftData[3] += analogRead(LeftLight4Pin);

    rightData[0] += analogRead(RightLight1Pin); //creates an array with all the right side sensors data
    rightData[1] += analogRead(RightLight2Pin);
    rightData[2] += analogRead(RightLight3Pin);
    rightData[3] += analogRead(RightLight4Pin);

    frontData[0] += analogRead(FrontLight1Pin); //creates an array with all the front sensors data
    frontData[1] += analogRead(FrontLight2Pin);
    frontData[2] += analogRead(FrontLight3Pin);
    frontData[3] += analogRead(FrontLight4Pin);

    backData[0] += analogRead(BackLight1Pin); //creates an array with all the back sensors data
    backData[1] += analogRead(BackLight2Pin);
    backData[2] += analogRead(BackLight3Pin);
    backData[3] += analogRead(BackLight4Pin);

    for (int i = 0; i < 4; i++) { //loops through the left sensors data, if the value is greater than the threshold for white, the value is set to 1 if no, 0
        if (leftData[i] > leftThresholds[i]) {
            Left[i] = 1;
        } else {
            Left[i] = 0;
        }
    }
    for (int i = 0; i < 4; i++) { //loops through the right sensors data, if the value is greater than the threshold for white, the value is set to 1 if no, 0
        if (rightData[i] > rightThresholds[i]) {
            Right[i] = 1;
        } else {
            Right[i] = 0;
        }
    }
    for (int i = 0; i < 4; i++) { //loops through the front sensors data, if the value is greater than the threshold for white, the value is set to 1 if no, 0
        if (frontData[i] > frontThresholds[i]) {
            Front[i] = 1;
        } else {
            Front[i] = 0;
        }
    }
    for (int i = 0; i < 4; i++) { //loops through the back sensors data, if the value is greater than the threshold for white, the value is set to 1 if no, 0
        if (backData[i] > backThresholds[i]) {
            Back[i] = 1;
        } else {
            Back[i] = 0;
        }
    }

    //putting all the data into one large array, makes it easier to manage the information     FIX FIX FIX FIX FIX FIX FIX FIX NEEDS TO BE LEFT1, LEFT,2 LEFT3, LEFT4, RIGHT1, RIGHT2 AND SO ON REFER TO LINES >164 FOR INFO DUMBASSSSSSS
    // finalLightData[0] += Front[0]; // 0-3 contains outer most sensor <----------- THIS IS FUCKED FIX!
    // finalLightData[1] += Right[0];
    // finalLightData[2] += Back[0];
    // finalLightData[3] += Left[0];
    //
    // finalLightData[4] += Front[1]; // 4-7 contains 2nd most outer sensor <-
    // finalLightData[5] += Right[1];
    // finalLightData[6] += Back[1];
    // finalLightData[7] += Left[1];
    //
    // finalLightData[8] += Front[2]; // 8-11 contains second closest to the middle of the robot <-
    // finalLightData[9] += Right[2];
    // finalLightData[10] += Back[2];
    // finalLightData[11] += Left[2];
    //
    // finalLightData[12] += Front[3]; // 12-15 contains the closest to the center of the robot <-
    // finalLightData[13] += Right[3];
    // finalLightData[14] += Back[3];
    // finalLightData[15] += Left[3];

    //This needs to be in the order of FRONT, RIGHT, BACK, LEFT [Around the circle in a clockwise pattern]
    finalLightData[0] += Front[0]; //FRONT
    finalLightData[1] += Front[1];
    finalLightData[2] += Front[2];
    finalLightData[3] += Front[3];

    finalLightData[4] += Right[0]; //RIGHT
    finalLightData[5] += Right[1];
    finalLightData[6] += Right[2];
    finalLightData[7] += Right[3];

    finalLightData[8] += Back[0]; //BACK
    finalLightData[9] += Back[1];
    finalLightData[10] += Back[2];
    finalLightData[11] += Back[3];

    finalLightData[12] += Left[0]; //LEFT
    finalLightData[13] += Left[1];
    finalLightData[14] += Left[2];
    finalLightData[15] += Left[3];

//God damn Im Stoopid //This crap was from when I was manually setting values to test that the code worked
    // finalLightData[0] += 1; // 0-3 contains outer most sensor
    // finalLightData[1] += 0;
    // finalLightData[2] += 0;
    // finalLightData[3] += 0;
    //
    // finalLightData[4] += 0; // 4-7 contains 2nd most outer sensor
    // finalLightData[5] += 0;
    // finalLightData[6] += 0;
    // finalLightData[7] += 0;
    //
    // finalLightData[8] += 0; // 8-11 contains second closest to the middle of the robot
    // finalLightData[9] += 0;
    // finalLightData[10] += 0;
    // finalLightData[11] += 0;
    //
    // finalLightData[12] += 0; // 12-15 contains the closest to the center of the robot
    // finalLightData[13] += 0;
    // finalLightData[14] += 0;
    // finalLightData[15] += 0;


    for(int i = 0; i < 16; i++){ //checks to see if the front sensors are seeing white
        if(finalLightData[i] >= 1){
                if(i <= 3){
                  lightSide = 1; //lightside is the variable used to know which quadrant of the robot the ball is in [Front, Right, Back, Left]
                  //Serial.println("LightSide = 1");
                }
                else if(i >= 4 && i <= 7){ //checks to see if the right side sensors are seeing white
                  lightSide = 2;
                  //Serial.println("LightSide = 2");
                }
                else if(i >= 8 && i <= 11){ //checks to see if the back sensors are seeing white
                  lightSide = 3;
                  //Serial.println("LightSide = 3");
                }
                else if(i >= 12 && i <= 15){ //checks to see if the left side sensors are seeing white
                  lightSide = 4;
                  //Serial.println("LightSide = 4");
                }
            }
        }

    if(warningTSOP > 17 || warningTSOP < 3){ //checking if the tsop is between 17 and 3 which is the front of the robot
        if(lightSide == 1){ //Checking if the white line is detected in the front quadrant (IDK why this isnt in the line above, but as it works and takes basically no more time to calculate ceebs fixing it.)
            for(int i = 0; i < 4; i++){
                if(finalLightData[i] >= 1){ //if the light piece for each sensor is 1 or true, run a switch to set a severity value (Same for the front as the sensors are in a line and not staggered in as on the sides)
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
    }
    else if(warningTSOP > 2 && warningTSOP < 8 && lightSide == 2){ //checking if the tsop is between 2 and 8 which is the right side of the robot
        for(int i = 4; i < 8; i++){
            if(finalLightData[i] >= 1){
                switch(i){
                    case 4: warningInt = 4; break; //Outermost
                    case 5: warningInt = 2; break;
                    case 6: warningInt = -4; break;
                    case 7: warningInt = -8; break; //Innermost
                }
            }
            if(warningInt == -8){
              break;
            }
        }
    }
    else if(warningTSOP > 8 && warningTSOP < 13 && lightSide == 3){ //checking if the tsop is between 8 and 13 which is the back of the robot
        for(int i = 8; i < 12; i++){
            if(finalLightData[i] >= 1){
                switch(i){
                    case 8: warningInt = 4; break; //Outermost
                    case 9: warningInt = 2; break;
                    case 10: warningInt = -4; break;
                    case 11: warningInt = -8; break; //Innermost
                }
            }
            if(warningInt == -8){
              break;
            }
        }
    }
    else if(warningTSOP > 12 && warningTSOP < 18 && lightSide == 4){ //checking if the tsop is between 12 and 18 which is the left side of the robot
        for(int i = 12; i < 16; i++){
            if(finalLightData[i] >= 1){
                switch(i){
                    case 12: warningInt = 4; break; //Outermost
                    case 13: warningInt = 2; break;
                    case 14: warningInt = -4; break;
                    case 15: warningInt = -8; break; //Innermost
                }
            }
            if(warningInt == -8){
              break;
            }
        }
    }
    //return 1.00;
    return warningInt/10; //return the warningInt as a decimal between 1.0 and -1.0
}

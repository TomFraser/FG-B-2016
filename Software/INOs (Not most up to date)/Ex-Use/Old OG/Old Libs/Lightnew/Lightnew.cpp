#include "LightNew.h"

light lightArray = light(LeftLight1Pin,LeftLight2Pin);

light::light(pin1, pin2, pin3, pin4, pin5, pin6, pin7, pin8, pin9, pin10, pin11, pin12, pin13, pim14, pin15, pin16){
    LeftLight1Pin = pin1;
    LeftLight2Pin = pin2;
    LeftLight3Pin = pin3;
    LeftLight4Pin = pin4;

    RightLight1Pin = pin5;
    RightLight2Pin = pin6;
    RightLight3Pin = pin7;
    RightLight4Pin = pin8;

    FrontLight1Pin = pin9;
    FrontLight2Pin = pin10;
    FrontLight3Pin = pin11;
    FrontLight4Pin = pin12;
}

float light::warning45(int warningTSOP){

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

    if(warningTSOP > 17 || warningTSOP < 3){
        if(lightSide==1){
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

#include <Light.h>
#include <Motor.h>
#include <Math.h>
#include <EEPROM.h>

Motor motorD(6, 24, 25, 33, 0, 1);  //PWM, IN1, IN2, SB, Ignore, Rev
Motor motorA(5, 8, 9, 32, 0, 1);
Motor motorB(3, 0, 1, 30, 0, 1);
Motor motorC(4, 2, 7, 31, 0, 1);

int pinArray[4] = {A0, A1, A2, A3};
int readLightArrayWhite[4];
int readLightArrayBlack[4];
int triggerValues[4] = {};

void setup(){
    pinMode(A0, INPUT); //Left
    pinMode(A1, INPUT); //Middle Left
    pinMode(A2, INPUT); //Middle Right
    pinMode(A3, INPUT); //Right

    pinMode(13, OUTPUT);

    pinMode(13, HIGH);
    delay(1000);
    pinMode(13, LOW);

    calibrate();
}

void loop(){
    if(analogRead(A0) >= triggerValues[0]){
        if(analogRead(A3) >= triggerValues[3]){
            motorA.set((-255/2));
            motorB.set((-208/2));
            motorC.set((208/2));
            motorD.set((255/2));
        }
        else{
            motorA.set((-255/2));
            motorB.set((-255/2));
            motorC.set((155/2));
            motorD.set((155/2));
        }
    }
    else{
        motorA.set((155/2));
        motorB.set((155/2));
        motorC.set((-255/2));
        motorD.set((-255/2));
    }
}

void ledBlink(int mSec){
    pinMode(13, HIGH);
    delay(mSec);
    pinMode(13, LOW);
    delay(mSec);
    pinMode(13, HIGH);
    delay(mSec);
    pinMode(13, LOW);
}

void calibrate(){
    ledBlink(100);
    delay(500);
    for(int i = 0; i < 4; i++){
        readLightArrayWhite[i] = analogRead(pinArray[i]);
    }
    ledBlink(100);
    delay(1000);
    ledBlink(100);
    for(int i = 0; i < 4; i++){
        readLightArrayBlack[i] = analogRead(pinArray[i]);
    }
    ledBlink(100);
    delay(500);

    for(int i = 0; i < 4; i++){
        triggerValues[i] = (readLightArrayWhite[i] - readLightArrayBlack[i]);
    }
}

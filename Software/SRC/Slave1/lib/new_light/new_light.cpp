#include <new_light.h>

new_light::new_light(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int pin7, int pin8, int pin9, int pin10, int pin11, int pin12, int pin13, int pin14, int pin15, int pin16){ //Left Right Back Front 4 of each
    calibrate();
    getReady();
}

void new_light::calculateArms(int bestTSOP, bool pixy, bool compass, int heading){
    sensorGrouping();
    for(int i = 0; i < 4; i++){
        if(analogRead(leftSensors[i]) >= leftArm_T[i]){ //leftArm is out
            arms::left = true;
            return 1;
        }
        else if(analogRead(rightSensors[i]) >= rightArm_T[i]){ //rightArm is out
            arms::right = true;
            return 2;
        }
        else if (analogRead(backSensors[i] >= backArm_T[i]){ //backArm is out
            arms::back = true;
            return 3;
        }
        else if (analogRead(frontSensors[i] >= frontArm_T[i]){ //frontArm is out
            arms::front = true;
            return 4;
        }
    }
    return 0;
}

void new_light::calculateIndiv(int bestTSOP, bool pixy, bool compass, int heading){

}

void new_light::calibrate(){
    int Sensors[16] = {pin1, pin2, pin3, pin4, pin5, pin6, pin7, pin8, pin9, pin10, pin11, pin12, pin13, pin14, pin15, pin16};
    int calibrateSensors[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    in thresholds[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    for(int i = 0; i < 10; i++){ //Taking ten readings of the sensors to be averaged
        calibrateSensors[0] = calibrateSensors[0] + analogRead(Sensors[0]);
        calibrateSensors[1] = calibrateSensors[1] + analogRead(Sensors[1]);
        calibrateSensors[2] = calibrateSensors[2] + analogRead(Sensors[2]);
        calibrateSensors[3] = calibrateSensors[3] + analogRead(Sensors[3]);
        calibrateSensors[4] = calibrateSensors[4] + analogRead(Sensors[4]);
        calibrateSensors[5] = calibrateSensors[5] + analogRead(Sensors[5]);
        calibrateSensors[6] = calibrateSensors[6] + analogRead(Sensors[6]);
        calibrateSensors[7] = calibrateSensors[7] + analogRead(Sensors[7]);
        calibrateSensors[8] = calibrateSensors[8] + analogRead(Sensors[8]);
        calibrateSensors[9] = calibrateSensors[9] + analogRead(Sensors[9]);
        calibrateSensors[10] = calibrateSensors[10] + analogRead(Sensors[10]);
        calibrateSensors[11] = calibrateSensors[11] + analogRead(Sensors[11]);
        calibrateSensors[12] = calibrateSensors[12] + analogRead(Sensors[12]);
        calibrateSensors[13] = calibrateSensors[13] + analogRead(Sensors[13]);
        calibrateSensors[14] = calibrateSensors[14] + analogRead(Sensors[14]);
        calibrateSensors[15] = calibrateSensors[15] + analogRead(Sensors[15]);
    }
    for(int i = 0; i < 16; i++){ //Averaging the sensors
        calibrateSensors[i] = calibrateSensors[i] / 10;
    }
}

void new_light::getReady(){
    for(int i = 0; i < 16; i++){
        thresholds[i] = calibrateSensors[i];
    }
}

void new_light::sensorGrouping(){//Probs wont end up using front sensors because the dont fucking work for some reason??????? @tfhulbert

    int leftSensors[4];
    int rightSensors[4];
    int backSensors[4];
    int frontSensors[4];

    int leftArm_T[4];
    int rightArm_T[4];
    int backArm_T[4];
    int frontArm_T[4];

    for(int i = 0; i < 4; i++){
        leftArm_T[i] = calibrateSensors[i];       //0,1,2,3 <-- Sensor Num
        rightArm_T[i] = calibrateSensors[4+i];    //4,5,6,7
        backArm_T[i] = calibrateSensors[8+i];     //8,9,10,11
        frontArm_T[i] = calibrateSensors[12+i];   //12,13,14,15

        leftSensors[i] = Sensors[i];
        rightSensors[i] = Sensors[4+i];
        backSensors[i] = Sensors[8+i];
        frontSensors[i] = Sensors[12+i];
    }
}

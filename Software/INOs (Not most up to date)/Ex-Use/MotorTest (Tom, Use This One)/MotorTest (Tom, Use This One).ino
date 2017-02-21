#include <Motor.h>

Motor motorA(3, 0, 1, 30, 0, 0);   //PWM, IN1, In2, SB, Ignore, Rev
Motor motorB(4, 2, 7, 31, 0, 0);
Motor motorC(5, 8, 9, 32, 0, 0);
Motor motorD(6, 24, 25, 33, 0, 0);


void setup(){
    pinMode(13, OUTPUT);
}

void loop(){
    digitalWrite(13, HIGH);

    //motorA.set(255);
    //motorB.set(-255);
    //motorC.set(255);
    //motorD.set(-255);

    //D, A, B, C

    //motorSpeed();
    for(int i = -25; i < 25; i++){
      motorA.set(i*10);
      motorB.set(i*10);
      motorC.set(i*10);
      motorD.set(i*10);
      delay(1000);
    }

} 

void motorSpeed(){
    motorD.set(-100*2.55);
    motorA.set(82*2.55);
    motorB.set(-82*2.55);
    motorC.set(100*2.55);
}

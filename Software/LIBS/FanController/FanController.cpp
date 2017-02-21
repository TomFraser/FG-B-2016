#include <FanContoller.h>

FanContoller::FanContoller(int pin1,int pin2) = { //The init function for fan controller, sets the PWM pin to output and TempPin to input to take reading from the temperature sensor
    PWMPin = pin1;
    TempPin = pin2;

    pinMode(PWMPin, OUTPUT); //PWM OUT
    pinMode(TempPin, INPUT); //Temp IN
}

float FanContoller::calcSpeeds(int rpm){ //0 to 6200 RPM
    return rpm * rpmToPWM; //rpmToPWM is a value to convert a rpm if 6200 to 255 PWM and so forth (0.041129032)
}

float setPWM_FANS(int TempPin){ //Returns PWM of 0-255 to set the motor controller to
    tempReturned = 0; //Resetting the temperature value
    tempReturned = digitalRead(TempPin); //grab the temperature value from the sensor using a (Hopefully digitalRead) function

    return calcSpeeds((int)(tempReturned * rpmPerDegree)); //return the temperature * rpmPerDegree where the latter is 77.5 (for each degree change the fan speeds up by 77.5)
}

#ifndef FanController_H
#define FanController_H

#define rpmToPWM 0.041129032 // converting rpm to pwm
#define PWMTorpm 24.31372549 //converting pwm to rpm
#define rpmPerDegree 77.5 //for each degree increase, an increase of 77.5 rpm occurs

struct speed { //Useless struct, not used right now but if each fan is on a seperate motor controller this might become usefull
    float up;
    float down;
    float left;
    float right;
};

class FanController{ //The class FanController
public:
    FanController(int pin1, int pin2); //PWM pin, Temp sensor pin The init function for the class
    float calcSpeeds(int rpm); //convert RPM to PWM
    float setPWM_FANS(int TempPin); //Assuming 1 temp sensor | calc RPM based on temperature
private:
    float currentSpeed; //A bunch of used ints that dont need to be public
    int pin1;
    int rpm;
    int PWMPin;
    int TempPin;
    int tempReturned;
};

#endif

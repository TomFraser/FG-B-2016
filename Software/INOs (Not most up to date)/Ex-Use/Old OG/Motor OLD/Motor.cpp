#include "Arduino.h"
#include "Motor.h"
#include "light.h"

Motor::Motor(int pwm_pin, int dir_pin, int brk_pin, uint8_t reversed){
    pwm = pwm_pin;
    dir = dir_pin;
    brk = brk_pin;
    rev = reversed;
    pinMode(pwm, OUTPUT);
    pinMode(dir, OUTPUT);
    pinMode(brk, OUTPUT);
}

void Motor::stop(uint8_t brake){
    digitalWrite(brk, brake);
    digitalWrite(pwm, LOW);
}

void Motor::set(int16_t value){
    digitalWrite(dir, value > 0 ? !rev : rev);
    analogWrite(pwm, value > 0 ? value : value*-1);
    digitalWrite(brk, LOW);
}

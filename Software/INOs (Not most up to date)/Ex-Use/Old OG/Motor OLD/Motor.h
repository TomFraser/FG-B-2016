#ifndef _MOTOR_H_
#define _MOTOR_H_

#include <stdint.h>

class Motor{
  private:
    int pwm, dir, brk;
    uint8_t rev;
  public:
    Motor(int pwm_pin, int dir_pin, int brk_pin, uint8_t reversed);
    void stop(uint8_t brake);
    void set(int16_t value);
};

#endif

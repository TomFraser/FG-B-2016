#ifndef SHFCOMMON_H
#define SHFCOMMON_H

#include <Arduino.h>

class SHFCOMMON{
public:
    SHFCOMMON(int input, int things, int others);
    bool degreesToRadians(int in);
    bool radiansToDegrees(int in);
    double doubleAbs(int value);
private:
    int thingsMain;
    int inputMain;
    int othersMain;
};

#endif

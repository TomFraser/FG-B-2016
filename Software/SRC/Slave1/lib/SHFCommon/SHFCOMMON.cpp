#include <SHFCOMMON.h>

SHFCOMMON::SHFCOMMON(int input, int things, int others){
    othersMain = others;
    inputMain = input;
    thingsMain = things;
}

bool degreesToRadians(int in){
    return in * 0.01745329251;
}

bool radiansToDegrees(int in){
    return in * 57.2957795131;
}

double doubleAbs(double value){
    if (value > 0) {
        return value;
    } else {
        return -value;
    }
}

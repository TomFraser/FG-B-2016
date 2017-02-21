#include "Maths.h"

double degreesToRadians(double degrees) {
    return degrees * ((double)PI / 180.0);
}

double radiansToDegrees(double radians) {
    return radians * ((180.0 / (double)PI));
}

double doubleAbs(double value) {
    if (value > 0) {
        return value;
    } else {
        return -value;
    }
}

double doubleMod(double value, double maxValue) {
    return fmod((value + maxValue), maxValue);
}

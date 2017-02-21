#include "LightSensorController.h"

LightSensorController::LightSensorController() {
    lsLeftOuter = LightSensor(LS_LEFT_OUTER, 0);
    lsLeftInner = LightSensor(LS_LEFT_INNER, 0);
    lsFrontOuter = LightSensor(LS_FRONT_OUTER, 0);
    lsFrontInner = LightSensor(LS_FRONT_INNER, 0);
    lsRightOuter = LightSensor(LS_RIGHT_OUTER, 0);
    lsRightInner = LightSensor(LS_RIGHT_INNER, 0);
    lsBackLeft = LightSensor(LS_BACK_OUTER, 0);
    lsBackRight = LightSensor(LS_BACK_INNER, 0);
}

LineLocation LightSensorController::readLineLocation() {
    bool lsLeftOuterOnWhite = lsLeftOuter.isOnWhite();
    bool lsLeftInnerOnWhite = lsLeftInner.isOnWhite();
    bool lsRightOuterOnWhite = lsRightOuter.isOnWhite();
    bool lsRightInnerOnWhite = lsRightInner.isOnWhite();
    bool lsFrontOuterOnWhite = lsFrontOuter.isOnWhite();
    bool lsFrontInnerOnWhite = lsFrontInner.isOnWhite();
    bool lsBackLeftOnWhite = lsLeftOuter.isOnWhite();
    bool lsBackRightOnWhite = lsRightOuter.isOnWhite();

    if (lsLeftOuterOnWhite || lsLeftInnerOnWhite) {
        if (lsFrontOuterOnWhite || lsFrontInnerOnWhite) {
            return LineLocation::cornerFrontLeft;
        } else if (lsBackLeftOnWhite || lsBackRightOnWhite) {
            return LineLocation::cornerBackLeft;
        } else {
            return LineLocation::left;
        }
    } else if (lsRightOuterOnWhite || lsRightInnerOnWhite) {
        if (lsFrontOuterOnWhite || lsFrontInnerOnWhite) {
            return LineLocation::cornerFrontRight;
        } else if (lsBackLeftOnWhite || lsBackRightOnWhite) {
            return LineLocation::cornerBackRight;
        } else {
            return LineLocation::right;
        }
    } else if (lsFrontOuterOnWhite || lsFrontInnerOnWhite) {
        return LineLocation::front;
    } else if (lsBackLeftOnWhite || lsBackRightOnWhite) {
        return LineLocation::back;
    } else {
        return LineLocation::field;
    }
}

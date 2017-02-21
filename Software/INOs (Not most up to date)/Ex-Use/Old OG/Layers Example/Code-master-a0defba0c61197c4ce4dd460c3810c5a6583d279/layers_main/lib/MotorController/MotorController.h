#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Arduino.h>
#include <Motor.h>
#include <MotorTI.h>
#include <Pins.h>
#include <Maths.h>
#include <LineLocation.h>
#include <Compass.h>
#include <Vector3D.h>

class MotorController {
public:
    Motor motorLeft;
    Motor motorRight;
    Motor motorBack;

    MotorController() {}
    MotorController(Compass *mainCompass);

    void goDirection(int direction, int power, LineLocation lineLocation = LineLocation::field, int rotation = 0);
    void goDirectionForTSOP(int TSOP, int power, LineLocation lineLocation = LineLocation::field, int rotation = 0);
    void goDirectionForBallDirection(int ballDirection, int power, LineLocation lineLocation = LineLocation::field, int rotation = 0);
    void rotateToBall(int ballDirection);
    void rotate(int power);
    void rotateToDirection(int direction, int power);
    void brake();
    int avoidLine(int direction, LineLocation lineLocation);

private:
    Compass *compass;

    int motorDir[12] = {
    	0,		// 0 Degrees
    	30,		// 30 Degrees
    	120,	// 60 Degrees
    	180,	// 90 Degrees
    	170,	// 120 Degrees
    	190,	// 150 Degrees
    	90,		// 180 Degrees
    	170,	// 210 Degrees
    	190,	// 240 Degrees
    	180,	// 270 Degrees
    	240,	// 300 Degrees
    	330		// 330 Degrees
    };
};

#endif

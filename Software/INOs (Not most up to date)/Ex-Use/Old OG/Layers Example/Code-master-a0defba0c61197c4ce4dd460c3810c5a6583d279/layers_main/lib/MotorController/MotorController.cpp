#include "MotorController.h"

MotorController::MotorController(Compass *mainCompass) {
    motorLeft = Motor(MOTOR_LEFT_PWM, MOTOR_LEFT_IN1, MOTOR_LEFT_IN2, MOTOR_LEFT_SB, 60, true);
    motorRight = Motor(MOTOR_RIGHT_PWM, MOTOR_RIGHT_IN1, MOTOR_RIGHT_IN2, MOTOR_RIGHT_SB, 300, true);
    motorBack = Motor(MOTOR_BACK_PWM, MOTOR_BACK_IN1, MOTOR_BACK_IN2, MOTOR_BACK_SB, 180, true);

    compass = mainCompass;
}

void MotorController::goDirection(int direction, int power, LineLocation lineLocation, int rotation) {
    direction = avoidLine(direction, lineLocation);

    double directionAngleRadians = degreesToRadians(360 - direction);

    double values[3] = {
        cos(degreesToRadians(motorLeft.motorAngle + 90) - directionAngleRadians),
        cos(degreesToRadians(motorRight.motorAngle + 90) - directionAngleRadians),
        cos(degreesToRadians(motorBack.motorAngle + 90) - directionAngleRadians)
    };

    double updatedPower = power / doubleAbs(max(max(doubleAbs(values[0]), doubleAbs(values[1])), doubleAbs(values[2])));

    int motorLeftPower = (int)(values[0] * updatedPower) + rotation;
    int motorRightPower = (int)(values[1] * updatedPower) + rotation;
    int motorBackPower = (int)(values[2] * updatedPower) + rotation;

    motorLeft.set(motorLeftPower);
    motorRight.set(motorRightPower);
    motorBack.set(motorBackPower);
}

void MotorController::goDirectionForTSOP(int TSOP, int power, LineLocation lineLocation, int rotation) {
    goDirection(motorDir[TSOP], power, lineLocation, rotation);
}

void MotorController::rotate(int power) {
    motorLeft.set(power);
    motorRight.set(power);
    motorBack.set(power);
}

void MotorController::rotateToDirection(int direction, int power) {
    int rotationZ = compass->readMagnetometer().z;

    while (rotationZ < (direction - 10) || rotationZ > (direction + 10)) {
        if (rotationZ < direction - 10) {
            rotate(power);
        } else if (rotationZ > direction + 10) {
            rotate(-power);
        }

        rotationZ = compass->readMagnetometer().z;
    }
}

void MotorController::goDirectionForBallDirection(int ballDirection, int power, LineLocation lineLocation, int rotation) {}

void MotorController::rotateToBall(int ballDirection) {
    if (ballDirection >= 180) {
        rotate((ballDirection - 180) / 2);
    } else {
        rotate(-ballDirection / 2);
    }
}

void MotorController::brake() {
    motorLeft.brake();
    motorRight.brake();
    motorBack.brake();
}

int MotorController::avoidLine(int direction, LineLocation lineLocation) {
    int correctedDirection = direction;

    switch (lineLocation) {
    case LineLocation::left:
        if (direction >= 270) {
            correctedDirection = 10;
        } else if (direction < 270 && direction >= 180) {
            correctedDirection = 170;
        }

        break;

    case LineLocation::right:
        if (direction <= 90) {
            correctedDirection = 350;
        } else if (direction > 90 && direction <= 180) {
            correctedDirection = 190;
        }

        break;

    case LineLocation::front:
        if (direction <= 90) {
            correctedDirection = 100;
        } else if (direction >= 270) {
            correctedDirection = 260;
        }

        break;

    case LineLocation::back:
        if (direction < 180 && direction >= 90) {
            correctedDirection = 80;
        } else if (direction >= 180 && direction <= 270) {
            correctedDirection = 280;
        }

        break;

    case LineLocation::cornerBackLeft:
        if (direction >= 90 && direction < 225) {
            correctedDirection = 80;
        } else if (direction >= 225) {
            correctedDirection = 10;
        }

        break;

    case LineLocation::cornerBackRight:
        if (direction <= 270 && direction > 135) {
            correctedDirection = 280;
        } else if (direction <= 135) {
            correctedDirection = 350;
        }

        break;

    case LineLocation::cornerFrontLeft:
        if (direction <= 90 || direction > 315) {
            correctedDirection = 100;
        } else if (direction <= 315 && direction >= 180) {
            correctedDirection = 10;
        }

        break;

    case LineLocation::cornerFrontRight:
        if (direction >= 270 || direction < 45) {
            correctedDirection = 260;
        } else if (direction >= 45 && direction <= 180) {
            correctedDirection = 190;
        }

        break;

    case LineLocation::field:
        break;
    }

    return correctedDirection;
}

#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Compass.h>
#include <GoalType.h>
#include <LightSensorController.h>
#include <LineLocation.h>
#include <MotorController.h>
#include <Pins.h>
#include <Pixy.h>
#include <Sonar.h>
#include <TSOPController.h>
#include <Vector3D.h>
#include <Maths.h>
#include <SoftwareSerial.h>
#include <Bluetooth.h>
#include <BluetoothData.h>

#define BLINK_DURATION 500

#define PIXY_THRESHOLD 10

MotorController motorController;
TSOPController tsopController;
Compass compass;

// LightSensorController lightSensorController;
// LineLocation lineLocation;

// Sonar sonarFront;
// Sonar sonarLeft;
// Sonar sonarRight;

// Pixy pixy;
// GoalType goalType = GoalType::blue;

long previousTime;
double heading = 0;

/* ----- Bluetooth Controlled Values ----- */

int speed = 0;
int rotation = 0;
bool sendTSOPData = false;

/* --------------------------------------- */

/* ---------- EEPROM Addresses ----------- */

enum EEPROMAddress: int {
	speedAddress,
	rotationAddress,
	sendTSOPDataAddress
};

/* --------------------------------------- */

/* --------------- Counters -------------- */

int TSOPCount = 0;
int blinkCount = 0;
bool blinkOn;

/* --------------------------------------- */

void setup() {
	Wire.begin();
	Serial.begin(9600);

	pinMode(LED_BUILTIN, OUTPUT);

	// lightSensorController = LightSensorController();

	// sonarLeft = Sonar(SONAR_LEFT_TRIG, SONAR_LEFT_ECHO);
    // sonarRight = Sonar(SONAR_RIGHT_TRIG, SONAR_RIGHT_ECHO);
    // sonarFront = Sonar(SONAR_FRONT_TRIG, SONAR_FRONT_ECHO);

	// pixy.init();

	compass.init();

	motorController = MotorController(NULL);
	tsopController = TSOPController();

	Bluetooth::init();

	// speed = EEPROM.read(EEPROMAddress::speedAddress);
	// rotation = EEPROM.read(EEPROMAddress::rotationAddress);
	// sendTSOPData = (bool) EEPROM.read(EEPROMAddress::sendTSOPDataAddress);

	Bluetooth::send("Speed: " + String(speed));
	Bluetooth::send("Rotation: " + String(rotation));
	Bluetooth::send("Send TSOP: " + String(sendTSOPData));
}


// void pixyData() {
// 	uint16_t blocks = pixy.getBlocks();

//     if (blocks) {
//         Block block = pixy.blocks[0];

//         if ((block.signature == 1 && goalType == GoalType::blue) || (block.signature == 2 && goalType == GoalType::yellow)) {
//             int blockMinX = block.x - (block.width / 2);
//             int blockMaxX = block.x + (block.width / 2);

//             int rotationZ = compass.readMagnetometer().z;

//             if (rotationZ < 180) {
//                 if (blockMinX > PIXY_THRESHOLD) {
//                     motorController.goDirection(270, blockMinX * 5, lineLocation, -50);
//                 } else {
//                     motorController.goDirection(0, 200, lineLocation);
//                 }
//             } else if (rotationZ >= 180) {
//                 if (blockMaxX < 319 - PIXY_THRESHOLD) {
//                     motorController.goDirection(90, blockMinX * 5, lineLocation, 50);
//                 } else {
//                     motorController.goDirection(0, 200, lineLocation);
//                 }
//             }
//         } else {
//             rotateToGoal();
//         }
//     } else {
//         rotateToGoal();
//     }
// }

// void rotateToGoal() {
// 	int rotationZ = compass.readMagnetometer().z;

//     if (rotationZ < 360 - COMPASS_TOLERANCE && rotationZ >= 180) {
//         motorController.goDirection(270, (rotationZ - 180) * 5, lineLocation, 50);
//     } else if (rotationZ > COMPASS_TOLERANCE && rotationZ < 180) {
//         motorController.goDirection(90, (rotationZ - 180) * 5, lineLocation, 50);
//     } else {
//         motorController.brake();
//     }
// }

// void rotateToZero() {
// 	int rotationZ = compass.readMagnetometer().z;

//     if (rotationZ < 360 - COMPASS_TOLERANCE && rotationZ >= 180) {
//         motorController.rotate((rotationZ - 180) * 5);
//     } else if (rotationZ > COMPASS_TOLERANCE && rotationZ < 180) {
//         motorController.rotate(-rotationZ * 5);
//     } else {
//         motorController.brake();
//     }
// }


void determineDirection() {
	// int rotationZ = compass.readMagnetometer().z;
    // int ballDirection = tsopController.ballDirection();

    // int correctionRotation = 0;

    // if (rotationZ < 360 - COMPASS_TOLERANCE && rotationZ >= 180) {
    //     correctionRotation = (rotationZ - 180) * 5;
    // } else if (rotationZ > COMPASS_TOLERANCE && rotationZ < 180) {
    //     correctionRotation = -rotationZ * 5;
    // }

    // if (ballDirection == -1) {
    //     rotateToZero();
    // } else if (ballDirection <= 270 || ballDirection >= 90) {
    //     if (rotationZ <= 270 && rotationZ >= 90) {
    //         motorController.rotateToBall(ballDirection);
    //     } else {
    //         motorController.goDirectionForTSOP(tsopController.currentTSOP, 200, lineLocation, correctionRotation);
    //     }
    // } else if ((rotationZ <= 270 && rotationZ >= 90) && (ballDirection >= 270 || ballDirection <= 90)) {
    //     if (ballDirection >= 270) {
    //         motorController.goDirection(90, 200, lineLocation, 100);
    //     } else {
    //         motorController.goDirection(270, 200, lineLocation, 100);
    //     }
    // } else if (ballDirection == 0) {
    //     int sonarFrontValue = sonarFront.read();

    //     if (sonarFrontValue < 2) {
    //         motorController.goDirection(0, sonarFrontValue * 10, lineLocation);
    //     } else {
    //         pixyData();
    //     }
    // } else {
    //     motorController.rotateToBall(ballDirection);
    // }

	int tsopNum = tsopController.bestTSOP();

	if (sendTSOPData) {
		Bluetooth::send(String(tsopNum), BluetoothDataType::TSOP);
	}

	double relativeHeading = 180.0 - heading;

	int correctionRotation = rotation;

	if (abs(relativeHeading) > 10) {
		correctionRotation += (relativeHeading);
	} else {
		correctionRotation = 0;
	}

	Bluetooth::send(String(correctionRotation));

	motorController.goDirectionForTSOP(tsopNum, speed, LineLocation::field, correctionRotation);
}

void updateTSOPS() {
	tsopController.updateValues();

	if (TSOPCount > TSOP_UPDATE) {
		TSOPCount = 0;

		determineDirection();
	} else {
		TSOPCount++;
	}
}

void blinkLED() {
    if (blinkCount < BLINK_DURATION) {
        blinkCount++;
    } else {
        blinkCount = 0;
        blinkOn = !blinkOn;

        digitalWrite(LED_BUILTIN, blinkOn ? HIGH : LOW);
    }
}

void bluetoothData() {
	BluetoothData data = Bluetooth::receive();

	switch (data.type) {
		case BluetoothDataType::motorSpeed:
			speed = constrain(data.value, 0, 255);
			EEPROM.update(EEPROMAddress::speedAddress, speed);
			break;

		case BluetoothDataType::motorRotation:
			rotation = constrain(data.value, -255, 255);
			EEPROM.update(EEPROMAddress::rotationAddress, rotation);
			break;

		case BluetoothDataType::TSOP:
			sendTSOPData = (bool) data.value;
			EEPROM.update(EEPROMAddress::sendTSOPDataAddress, (int) sendTSOPData);
			break;

		default:
			break;
	}
}

void compassData() {
	double reading = (double) compass.readGyroscope().z;

	long currentTime = micros();
 	heading += (((double)(currentTime - previousTime) / 1000000.0) * reading) + 180;
	heading = doubleMod(heading, 360.0);

	previousTime = currentTime;
}

void loop() {
	bluetoothData();

	if (blinkCount % 50 == 0) {
		compassData();
	}

	updateTSOPS();
	blinkLED();
}

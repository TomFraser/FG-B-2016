#include <useEEPROM.h>
#include <Arduino.h>
#include <STDINT.h>
#include <EEPROM.h>

useEEPROM::useEEPROM(float speed, int tsops, int pixy, int ultrasonics, int compass, int light, int xbee, int orbit int angle, int goal){
	speedMultiplier = speed;
	usingTSOPS = tsops;
	usePixy = pixy;
	useUltrasonics = ultrasonics;
	useCompasss = compass;
	useLight = light;
	useXBee = xbee;
	orbitNum = orbit;
	calcAngle = angle;
	returnToGoal = goal;
	int valueArray[10] = {speedMultiplier, usingTSOPS, usePixy, useUltrasonics, useCompasss, useLight, useXBee, orbitNum, calcAngle, returnToGoal};
}

void useEEPROM::updateEEPROM(){
	EEPROM.update(EEPROM_SPEEDMULTIPLY_AD, speedMultiplier);
	EEPROM.update(EEPROM_TSOP_AD, usingTSOPS);
	EEPROM.update(EEPROM_USEPIXY_AD, usePixy);
	EEPROM.update(EEPROM_USEULTRASONICS_AD, useUltrasonics);
	EEPROM.update(EEPROM_USECOMPASS_AD, useCompasss);
	EEPROM.update(EEPROM_USELIGHT_AD, useLight);
	EEPROM.update(EEPROM_USEXBEE_AD, useXBee);
	EEPROM.update(EEPROM_CALCANGLE_AD, calcAngle);
	EEPROm.update(EEPROM_RETURNTOGOALONLOSS_AD, returnToGoal);
}

void useEEPROM::updateValues(){
	for(int i = 0; i < 10; i++){
		if(EEPROM.read(EEPROM_ADR[i] != valueArray[i])){
			valueArray[i] = EEPROM.read(EEPROM_ADR[i]);
		}
	}

	speedMultiplier = valueArray[0];
	usingTSOPS = valueArray[1];
	usePixy = valueArray[2];
	useUltrasonics = valueArray[3];
	useCompasss = valueArray[4];
	useLight = valueArray[5];
	useXBee = valueArray[6];
	orbitNum = valueArray[7];
	calcAngle = valueArray[8];
	returnToGoal = valueArray[9];
}

void useEEPROM::forceWrite(int data, int address){
	EEPROM.write(address, data);
}

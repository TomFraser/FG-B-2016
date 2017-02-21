#ifndef useEEPROM_H
#define useEEPROM_H

//EEPROM Locations in memory: The Teensy contains 4096 Bytes of EEPROM (the values held in eeprom are 0-255)
#define EEPROM_SPEEDMULTIPLY_AD 1
#define EEPROM_TSOP_AD 1
#define EEPROM_USEPIXY_AD 1
#define EEPROM_USEULTRASONICS_AD 1
#define EEPROM_USECOMPASS_AD 1
#define EEPROM_USELIGHT_AD 1
#define EEPROM_USEXBEE_AD 1
#define EEPROM_USEORBITNUM_AD 1
#define EEPROM_CALCANGLE_AD 1
#define EEPROM_RETURNTOGOALONLOSS_AD 1
#define EEPROM_LIGHTTHRESHOLDS 1

class useEEPROM{

public:
    useEEPROM(float speed, int tsops, int pixy, int ultrasonics, int compass, int light, int xbee, int orbit, int angle, int goal);
    void updateEEPROM();
    void updateValues();
    void forceWrite(int data, int address);

private:
    float speedMultiplier;
    int usingTSOPS;
    int usePixy;
    int useUltrasonics;
    int useCompasss;
    int useLight;
    int useXBee;
    int orbitNum;
    int calcAngle;
    int returnToGoal;
    int EEPROM_ADR[10] = {EEPROM_SPEEDMULTIPLY_AD, EEPROM_TSOP_AD, EEPROM_USEPIXY_AD, EEPROM_USEULTRASONICS_AD, EEPROM_USECOMPASS_AD, EEPROM_USELIGHT_AD, EEPROM_USEXBEE_AD, EEPROM_USEORBITNUM_AD, EEPROM_CALCANGLE_AD, EEPROM_RETURNTOGOALONLOSS_AD};

};

#endif

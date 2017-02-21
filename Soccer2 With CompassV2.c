
#pragma config(Sensor, S1,     FIR,            sensorI2CCustom)
#pragma config(Sensor, S2,     BIR,            sensorI2CCustom)
#pragma config(Sensor, S3,     compass,        sensorI2CHiTechnicCompass)
#pragma config(Sensor, S4,     light,          sensorLightActive)
#include "drivers\tris10-findball.h"           !!*//

int ADJRNG = 7;
int ADJSPD = 80;
int COMPRelative;
int COMPCompare;
int str;

task main()
{
	wait10Msec(10);
  	const int COMPOrigin = SensorRaw[S3];
	while(true){
		COMPRelative = SensorValue[S3];
		COMPCompare = COMPOrigin - COMPRelative;
		nxtDisplayTextLine(1, "%i",COMPOrigin,);
		nxtDisplayTextLine(2, "%i",COMPRelative,);
		nxtDisplayTextLine(3, "%i",COMPCompare,);

		if(COMPCompare != -ADJRNG - ADJRNG){
			nxtDisplayTextLine(4, "FIRST IF");
				if((T10FBreadStrength(FIR) + 1) > T10FBreadStrength(BIR)){
					nxtDisplayTextLine(5, "Second IF");
	    			while (T10FBreadStrength(FIR) < 100){
						nxtDisplayTextLine(6, "Can't See");
						COMPRelative = SensorValue[S3];
						COMPCompare = COMPOrigin - COMPRelative;
						nxtDisplayTextLine(1, "%i",COMPOrigin,);
						nxtDisplayTextLine(2, "%i",COMPRelative,);
						nxtDisplayTextLine(3, "%i",COMPCompare,);
						str = T10FBreadStrength(FIR);
						nxtDisplayTextLine(8, "%i",str,);

  						motor[motorA] = 0;
						motor[motorA] = 100;
						motor[motorB] = 0;				//Back
						motor[motorB] = 72;
						motor[motorC] = 0;
						motor[motorC] = 0;
						if(COMPCompare != -ADJRNG - ADJRNG) {
							break;
						}
					}
					while(T10FBreadDir(FIR) == 5){
	    				nxtDisplayTextLine(6, "WHILE5");
						COMPRelative = SensorValue[S3];
						COMPCompare = COMPOrigin - COMPRelative;
						nxtDisplayTextLine(1, "%i",COMPOrigin,);
						nxtDisplayTextLine(2, "%i",COMPRelative,);
						nxtDisplayTextLine(3, "%i",COMPCompare,);
						str = T10FBreadStrength(FIR);
						nxtDisplayTextLine(8, "%i",str,);
	  					motor[motorA] = 0;
						motor[motorA] = 100;
						motor[motorB] = 0;				//Back
						motor[motorB] = 72;
						motor[motorC] = 0;
						motor[motorC] = 0;
						wait1Msec(100);
	    			}

	    			while (T10FBreadDir(FIR) == 4){
	    			    nxtDisplayTextLine(6, "WHILE2");
						COMPRelative = SensorValue[S3];
						COMPCompare = COMPOrigin - COMPRelative;
						nxtDisplayTextLine(1, "%i",COMPOrigin,);
						nxtDisplayTextLine(2, "%i",COMPRelative,);
						nxtDisplayTextLine(3, "%i",COMPCompare,);
						str = T10FBreadStrength(FIR);
						nxtDisplayTextLine(8, "%i",str,);
						motor[motorA] = 0;
						motor[motorA] = 0;
						motor[motorB] = 0;				//Right
						motor[motorB] = 100;
						motor[motorC] = 0;
						motor[motorC] = -95;
								wait10Msec(20);
						motor[motorA] = 0;
						motor[motorA] = -68;
						motor[motorB] = 0;				//Right
						motor[motorB] = 68;
						motor[motorC] = 0;
						motor[motorC] = -100;
							wait10Msec(5);
					}
					while (T10FBreadDir(FIR) == 3){
						nxtDisplayTextLine(6, "WHILE3");
						COMPRelative = SensorValue[S3];
						COMPCompare = COMPOrigin - COMPRelative;
						nxtDisplayTextLine(1, "%i",COMPOrigin,);
						nxtDisplayTextLine(2, "%i",COMPRelative,);
						nxtDisplayTextLine(3, "%i",COMPCompare,);
						str = T10FBreadStrength(FIR);
						nxtDisplayTextLine(8, "%i",str,);
  						motor[motorA] = 0;
						motor[motorA] = -100;
						motor[motorB] = 0;				//Forwards
						motor[motorB] = -72;
						motor[motorC] = 0;
						motor[motorC] = 0;
						wait1Msec(300);
					}
					while (T10FBreadDir(FIR) == 2){
						nxtDisplayTextLine(6, "WHILE4");
						COMPRelative = SensorValue[S3];
						COMPCompare = COMPOrigin - COMPRelative;
						nxtDisplayTextLine(1, "%i",COMPOrigin,);
						nxtDisplayTextLine(2, "%i",COMPRelative,);
						nxtDisplayTextLine(3, "%i",COMPCompare,);
						str = T10FBreadStrength(FIR);
						nxtDisplayTextLine(8, "%i",str,);
						motor[motorA] = 0;
						motor[motorA] = 100;
						motor[motorB] = 0;				//Left
						motor[motorB] = 0;
						motor[motorC] = 0;
						motor[motorC] = 92;
						wait10Msec(20);
						motor[motorA] = 0;
						motor[motorA] = 68;
						motor[motorB] = 0;				//Left
						motor[motorB] = -68;
						motor[motorC] = 0;
						motor[motorC] = 100;
						wait10Msec(5);
					}
					while (T10FBreadDir(FIR) == 1){
						nxtDisplayTextLine(6, "WHILE5");
						COMPRelative = SensorValue[S3];
						COMPCompare = COMPOrigin - COMPRelative;
						nxtDisplayTextLine(1, "%i",COMPOrigin,);
						nxtDisplayTextLine(2, "%i",COMPRelative,);
						nxtDisplayTextLine(3, "%i",COMPCompare,);
						str = T10FBreadStrength(FIR);
						nxtDisplayTextLine(8, "%i",str,);
					  	motor[motorA] = 0;
						motor[motorA] = 100;
						motor[motorB] = 0;				//Back
						motor[motorB] = 72;
						motor[motorC] = 0;
						motor[motorC] = 0;
						wait1Msec(50);
					}
					while (T10FBreadStrength(BIR) > 100) {
						nxtDisplayCenteredTextLine(6, "Behind");
						COMPRelative = SensorValue[S3];
						COMPCompare = COMPOrigin - COMPRelative;
						nxtDisplayTextLine(1, "%i",COMPOrigin,);
						nxtDisplayTextLine(2, "%i",COMPRelative,);
						nxtDisplayTextLine(3, "%i",COMPCompare,);
						str = T10FBreadStrength(FIR);
						nxtDisplayTextLine(8, "%i",str,);
						motor[motorA] = 0;
						motor[motorA] = 100;
						motor[motorB] = 0;				//Backwards
						motor[motorB] = 95;
						motor[motorC] = 0;
						motor[motorC] = 0;
					}
				}
			}



			else(COMPCompare != -ADJRNG-ADJRNG);{
				while(COMPCompare <= -ADJRNG){
					COMPRelative = SensorValue[S3];
					COMPCompare = COMPOrigin - COMPRelative;
					nxtDisplayTextLine(1, "%i",COMPOrigin,);
					nxtDisplayTextLine(2, "%i",COMPRelative,);
					nxtDisplayTextLine(3, "%i",COMPCompare,);
					motor[motorA] = 0;
					motor[motorA] = ADJSPD;
					motor[motorB] = 0;
					motor[motorB] = -ADJSPD;
					motor[motorC] = 0;
					motor[motorC] = -ADJSPD;
				}
				motor[motorA] = 0;
				motor[motorB] = 0;
				motor[motorC] = 0;

				while(COMPCompare >= ADJRNG){
					COMPRelative = SensorValue[S3];
					COMPCompare = COMPOrigin - COMPRelative;
					nxtDisplayTextLine(1, "%i",COMPOrigin,);
					nxtDisplayTextLine(2, "%i",COMPRelative,);
					nxtDisplayTextLine(3, "%i",COMPCompare,);
					motor[motorA] = 0;
					motor[motorA] = -ADJSPD;
					motor[motorB] = 0;
					motor[motorB] = ADJSPD;
					motor[motorC] = 0;
					motor[motorC] = ADJSPD;
				}
				motor[motorA] = 0;
				motor[motorB] = 0;
				motor[motorC] = 0;
			}
	}
}

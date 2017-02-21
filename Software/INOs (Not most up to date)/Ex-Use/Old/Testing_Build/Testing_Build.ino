#include "Light.h"
#include "Motor.h"

light lightArray = light(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,20);

int moveArray[21][4] = {
  {0,0,0,0},
  {-100, -82, 82, 100}, //Clockwise (From Middle Front)
  {-68, -91, 46, 100},
  {-41, -99, 16, 100},
  {-11, -100, -16, 92},
  {23, -100, -51, 83},
  {71, -100, -100, 71},
  {83, -51, -100, 23},
  {92, -16, -100, -11},
  {100, 16, -99, -41},
  {100, 46, -91, -68},
  {100, 82, -82, -100},
  {68, 91, -46, -100},
  {41, 99, -16, -100},
  {11, 100, 16, -92},
  {-23, 100, 51, -83},
  {-71, 100, 100, -71},
  {-83, 51, 100, -23},
  {-92, 16, 100, 11},
  {-100, -16, 99, 41},
  {-100, -46, 91, 68},
};
Motor motorA(0,1,1,0);
int orbit[21] = {0, 1, 1, 5, 7, 9, 10, 11, 12, 13, 14, 7, 8, 9, 10, 12, 11, 13, 15, 17, 1}; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  //Serial.println(lightArray.warning45(1));
  Serial.println(moveArray[orbit[1]][0] * lightArray.warning45(1));
  delay(1000);
}

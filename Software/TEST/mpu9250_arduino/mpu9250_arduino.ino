#include <Wire.h>
#include <SPI.h>
#include <Madgwick.h>
#include <Vector3D.h>
#include <Compass.h>

#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C

#define    GYRO_FULL_SCALE_250_DPS    0x00
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18

#define    ACC_FULL_SCALE_2_G        0x00
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18

int homeHeading;
int currentHeading;
int difference;

Compass Compass;
void setup()
{
  Wire.begin();
  Serial.begin(9600);

 Compass.start();
 homeHeading = Compass.pitchRollYaw().yaw;
 delay(1000);
}

void loop()
{
  compassData();
  //delay(100);
}

void compassData(){
  CompassData compassData = Compass.pitchRollYaw();
  int currentHeading = compassData.yaw;
  difference = currentHeading - homeHeading;
  Serial.println(currentHeading);
}

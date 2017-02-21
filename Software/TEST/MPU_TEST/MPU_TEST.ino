#include <Motor.h>
#include <Light.h>
#include <Wire.h>
#include <Madgwick.h>

Motor motorD(6, 24, 25, 33, 0, 1);
Motor motorA(5, 8, 9, 32, 0, 1);
Motor motorB(3, 0, 1, 30, 0, 1);   //PWM, IN1, In2, SB, Ignore, Rev
Motor motorC(4, 2, 7, 31, 0, 1);

Madgwick compass;

void setup(){
    Wire.begin();
    Serial.begin(9600);

    // Set accelerometers low pass filter at 5Hz
    I2CwriteByte(MPU9250_ADDRESS,29,0x06);
    // Set gyroscope low pass filter at 5Hz
    I2CwriteByte(MPU9250_ADDRESS,26,0x06);


    // Configure gyroscope range
    I2CwriteByte(MPU9250_ADDRESS,27,GYRO_FULL_SCALE_1000_DPS);
    // Configure accelerometers range
    I2CwriteByte(MPU9250_ADDRESS,28,ACC_FULL_SCALE_4_G);
    // Set by pass mode for the magnetometers
    I2CwriteByte(MPU9250_ADDRESS,0x37,0x02);

    // Request continuous magnetometer measurements in 16 bits
    I2CwriteByte(MAG_ADDRESS,0x0A,0x16);

    pinMode(13, OUTPUT);
    Timer1.initialize(10000);         // initialize timer1, and set a 1/2 second period
    Timer1.attachInterrupt(callback);  // attaches callback() as a timer overflow interrupt
}

void loop(){
    
}

void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();

  // Read Nbytes
  Wire.requestFrom(Address, Nbytes);
  uint8_t index=0;
  while (Wire.available())
    Data[index++]=Wire.read();
}


// Write a byte (Data) in device (Address) at register (Register)
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}

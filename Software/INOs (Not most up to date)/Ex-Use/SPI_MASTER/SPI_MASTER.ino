#include <t3spi.h>

T3SPI SPI_MASTER;

#define dataLength 1

volatile uint8_t data[dataLength] = {420};
volatile uint8_t recieveData[dataLength] = {0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI_MASTER.begin_MASTER(14, 11, 12, 10, CS_ActiveLOW/*CLK, MOSI, MISO, SS, CS_ActiveLOW*/);
  SPI_MASTER.setCTAR(0, 8, SPI_MODE0, LSB_FIRST, SPI_CLOCK_DIV4);

  //data[0] = 255;

}

void loop() {
  // put your main code here, to run repeatedly:
  SPI_MASTER.timeStamp1 = micros();
  SPI_MASTER.txrx8(data, recieveData, dataLength, 0, /*ss*/ 14);
  SPI_MASTER.timeStamp2 = micros();

  Serial.println(recieveData[0]);
  SPI_MASTER.packetCT = 0;

  delay(1000);
}

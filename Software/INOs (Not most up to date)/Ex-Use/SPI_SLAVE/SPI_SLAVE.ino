#include <t3spi.h>
#define dataLength 1

T3SPI SPI_SLAVE;

volatile uint8_t data[dataLength] = {};
volatile uint8_t recieveData[dataLength] = {};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  SPI_SLAVE.begin_SLAVE(14, 11, 12, 10); // CLK, MOSI, MISO, SS
  SPI_SLAVE.setCTAR_SLAVE(8, SPI_MODE0);

  NVIC_ENABLE_IRQ(IRQ_SPI0);

data[0] = 69;

}

void loop() {
  // put your main code here, to run repeatedly:
  if(SPI_SLAVE.dataPointer == 0 && SPI_SLAVE.packetCT == 0){
    SPI_SLAVE.timeStamp1 = micros();
  }
  if(SPI_SLAVE.packetCT == 1){
    SPI_SLAVE.timeStamp2 = micros();
  }

}

void spi0_isr(void){
  SPI_SLAVE.rxtx8(recieveData, data, dataLength);
  Serial.println(data[0]);
}

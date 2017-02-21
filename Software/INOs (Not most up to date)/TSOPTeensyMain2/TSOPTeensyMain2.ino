#include <t3spi.h>
//#include <SPI.h>

#define counter_max 128
#define SENSORS 20
#define PWR_PIN_1 27
#define PWR_PIN_2 28

#define dataLength 1

volatile uint8_t dataOut[dataLength] = {};
volatile uint8_t dataIn[dataLength] = {};

byte sensors[SENSORS] = {0,1,2,3,4,5,6,7,8,9,15,16,17,20,21,22,23,24,25,26};
byte bestSensor = 0;
byte bestValue = 0;
byte counter = 0;
byte returnData[SENSORS];

T3SPI TSOP_SLAVE;

void setup(){
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    Serial.begin(9600);
    TSOP_SLAVE.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);
    TSOP_SLAVE.setCTAR_SLAVE(8, SPI_MODE0);
    NVIC_ENABLE_IRQ(IRQ_SPI0);

    pinMode(PWR_PIN_1, OUTPUT);
    pinMode(PWR_PIN_2, OUTPUT);
    digitalWrite(PWR_PIN_1, HIGH);
    digitalWrite(PWR_PIN_2, HIGH);

    for(int i = 0; i < SENSORS; i++){
        pinMode(sensors[i], INPUT);
    }
}

void loop(){
    pinMode(PWR_PIN_1, HIGH);
    pinMode(PWR_PIN_2, HIGH);
    for(int i = 0; i < SENSORS; i++){
        if(sensors[i] < 255){
            returnData[i] += (digitalRead(sensors[i]) == HIGH ? 0 : 1);
        }
    }

    counter++;
    if(counter >= counter_max){
        counter = 0;

        bestSensor = 0;
        bestValue = 0;
        dataOut[0] = 0;

        for(int i = 0; i < SENSORS; i++){
            if(returnData[i] < 20){
                returnData[i] = 0;
            }
            if(returnData[i] > bestValue){
                bestSensor = i;
                dataOut[0] = i;
                bestValue = returnData[i];
                Serial.println(dataOut[0]);
            }
            returnData[i] = 0;
        }
        counter = 0;

        pinMode(PWR_PIN_1, LOW);
        pinMode(PWR_PIN_2, LOW);
        //Serial.println(bestSensor);
        //Serial.println(bestValue);
    }
}

void spi0_isr(void){
    Serial.println("Entering SPI");
    TSOP_SLAVE.rxtx8(dataIn, dataOut, dataLength);
}

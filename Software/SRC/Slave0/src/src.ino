//Coded with <3 by Thomas Fraser
#include <t3spi.h>

#define MAX_COUNTER 128
#define SENSORS 20
#define UNLOCK_PIN 27

#define dataLength 1

#define robotRadius 10.5

T3SPI TSOP_SLAVE;

byte sensors[SENSORS] = {0,1,2,3,4,5,6,7,8,9,15,16,17,20,21,22,23,24,25,26};
byte IR_SENSOR = 0;
byte counter = 0;
byte values[SENSORS];

long beginMicros;
long currentMicros;

volatile uint16_t dataOut[dataLength] = {};
volatile uint16_t dataIn[dataLength] = {};

void setup() {
    pinMode(13, OUTPUT);
    Serial.begin(9600);

    TSOP_SLAVE.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);
    TSOP_SLAVE.setCTAR_SLAVE(16, SPI_MODE0);
    NVIC_ENABLE_IRQ(IRQ_SPI0);

    pinMode(UNLOCK_PIN, OUTPUT);
    digitalWrite(UNLOCK_PIN, HIGH);

    for (byte i = 0;i < SENSORS;i++) {
        values[i] = 0;
    pinMode(sensors[i], INPUT);
    }

    digitalWrite(13, HIGH); //Tells us when the Teensy is Ready to go

    long beginMicros = micros();
}

void loop() {
    for (byte i = 0;i < SENSORS;i++) {
      if (sensors[i] < 255) {
        values[i] += (digitalRead(sensors[i]) == HIGH ? 0 : 1);
      }
    }

    counter++;

    if (counter >= MAX_COUNTER) {
      digitalWrite(UNLOCK_PIN, LOW);
      delay(2);
      counter = 0;

      byte b_index = 0;

      byte b_value = 0;

      dataOut[0] = 0;

      for (byte i = 0;i < SENSORS;i++) {
          if(values[i] < 30){
              values[i] = 0;
          }
        if (values[i] > b_value) {
          b_index = i;
          calcAngle(b_index);
          dataOut[0] = i;
          b_value = values[i];
        }

        values[i] = 0;
      }

      IR_SENSOR = b_index;

      counter = 0;

      digitalWrite(UNLOCK_PIN, HIGH);
    }
}

void spi0_isr(void){ //Wake up in the morning... TRIGGERED [The SPI]
    //Serial.println(dataOut[0]);
    TSOP_SLAVE.rxtx16(dataIn, dataOut, dataLength);
}

int calcAngle(int sensor){ //This shit is weird, basically move on an angle as close to the ball as possible without touching, wouldnt recomend using this as it probs doesnt work
    int directSensor = sensor;
    int newMoveArray[20] = {0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 5, 17, 18, 19, 0, 0, 0, 0, 0, 0};

    int degreeSensor = (directSensor - newMoveArray[directSensor])*18;
    int oppositeAngles = (180 - degreeSensor)/2;
    return oppositeAngles - (newMoveArray[sensor]*18);
}

// int calcMovement(mod_Movement move){
//     //some stuff to do with the best sensor and its two surrounding sensors
// }
//
// struct mod_Movement{
//     int top;
//     int left;
//     int right;
//     int top_s;
//     int left_s;
//     int right_s;
// };

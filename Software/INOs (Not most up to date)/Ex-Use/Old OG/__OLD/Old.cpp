#define TSOP1 0
#define TSOP2 1
#define TSOP3 2
#define TSOP4 3
#define TSOP5 4
#define TSOP6 5
#define TSOP7 6
#define TSOP8 7
#define TSOP9 8
#define TSOP10 9
#define TSOP11 10
#define TSOP12 11
#define TSOP13 12
#define TSOP14 13
#define TSOP15 14
#define TSOP16 15
#define TSOP17 16
#define TSOP18 17
#define TSOP19 18
#define TSOP20 19

#define SENSORS 20

#define MAX_READING 5
#define MIN_READING 50

#define TSOPDegree 18

#define TSOP_POWER_PIN 1000

bool isUsingTrig = false;

int readArray[SENSORS];
int tempReadArray[SENSORS];
int bestSensor = 0;
int bestIndex = 0;
int foundSensor = 0;
byte values[20];

void setup(){
    sensorSetup();
    Serial.begin(115200);
}
void loop(){
    sensorActivate();
    copyData();
    filterData();
    if(isUsingTrig != true){
        foundSensor = findBest();
    }
    else{
        foundSensor = determineAverage();
    }
}

void sensorSetup() {
    pinMode(TSOP1, INPUT);
    pinMode(TSOP2, INPUT);
    pinMode(TSOP3, INPUT);
    pinMode(TSOP4, INPUT);
    pinMode(TSOP5, INPUT);
    pinMode(TSOP6, INPUT);
    pinMode(TSOP7, INPUT);
    pinMode(TSOP8, INPUT);
    pinMode(TSOP9, INPUT);
    pinMode(TSOP10, INPUT);
    pinMode(TSOP11, INPUT);
    pinMode(TSOP12, INPUT);
    pinMode(TSOP13, INPUT);
    pinMode(TSOP14, INPUT);
    pinMode(TSOP15, INPUT);
    pinMode(TSOP16, INPUT);
    pinMode(TSOP17, INPUT);
    pinMode(TSOP18, INPUT);
    pinMode(TSOP19, INPUT);
    pinMode(TSOP20, INPUT);
}

void sensorRead() {
    tempReadArray[0] = digitalRead(TSOP1);
    tempReadArray[1] = digitalRead(TSOP2);
    tempReadArray[2] = digitalRead(TSOP3);
    tempReadArray[3] = digitalRead(TSOP4);
    tempReadArray[4] = digitalRead(TSOP5);
    tempReadArray[5] = digitalRead(TSOP6);
    tempReadArray[6] = digitalRead(TSOP7);
    tempReadArray[7] = digitalRead(TSOP8);
    tempReadArray[8] = digitalRead(TSOP9);
    tempReadArray[9] = digitalRead(TSOP10);
    tempReadArray[10] = digitalRead(TSOP11);
    tempReadArray[11] = digitalRead(TSOP12);
    tempReadArray[12] = digitalRead(TSOP13);
    tempReadArray[13] = digitalRead(TSOP14);
    tempReadArray[14] = digitalRead(TSOP15);
    tempReadArray[15] = digitalRead(TSOP16);
    tempReadArray[16] = digitalRead(TSOP17);
    tempReadArray[17] = digitalRead(TSOP18);
    tempReadArray[18] = digitalRead(TSOP19);
    tempReadArray[19] = digitalRead(TSOP20);
}

void copyData() {
    for (int i = 0; i < SENSORS; i++) {
            tempReadArray[i] = readArray[i];
    }
}
void filterData() {
    for (int i = 0; i < SENSORS; i++) {
        if (readArray[i] > MAX_READING || readArray[i] < MIN_READING) {
                    readArray[i] = 0;
        }
    }
}

int findBest() {
    bestSensor = 0;
    bestIndex = 0;
    for (int i = 0; i < 21; i++) {
        if (readArray[i] > bestSensor) {
            bestSensor = readArray[i];
        }
    }
    bestIndex = bestSensor;
    return bestIndex;
}

int determineAverage() { // 1 on each side of bestSensor
    int oneUp = readArray[bestSensor + 1];
    int oneDown = readArray[bestSensor - 1];
    int originalTSOP = bestSensor;
    float averageTSOP = (oneUp + oneDown + originalTSOP) / 2;
    int averageDegree = averageTSOP * TSOPDegree;
    return averageDegree;
}
void sensorActivate(){
    digitalWrite(TSOP_POWER_PIN, HIGH);
    sensorRead();
    delayMicroseconds(1500);
    digitalWrite(TSOP_POWER_PIN, LOW);
}

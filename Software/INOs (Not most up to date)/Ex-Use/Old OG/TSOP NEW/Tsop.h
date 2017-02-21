#ifndef TSOP_H
#define TSOP_H

class tsop{

public:
    tsop();
    void setup();
    void read();
    void copyFilter();
    void findBest();
    int average();
    void activate();
    void push();

private:
    bool isUsingTrig = false;

    int readArray[20];
    int tempReadArray[20];
    int bestSensor = 0;
    int bestIndex = 0;
    int foundSensor = 0;
    byte values[20];

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
    #define SENSORS 20

};

#endif

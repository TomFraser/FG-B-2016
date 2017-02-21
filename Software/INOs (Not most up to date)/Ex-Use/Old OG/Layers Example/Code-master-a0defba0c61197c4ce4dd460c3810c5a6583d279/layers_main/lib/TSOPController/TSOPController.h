#ifndef TSOPCONTROLLER_H
#define TSOPCONTROLLER_H

#include <Arduino.h>
#include <Pins.h>

#define TSOP_NUM 12
#define TSOP_UPDATE 100

class TSOPController {
public:
    int currentTSOP;

    TSOPController();

    void updateValues();
    int bestTSOP();
    int ballDirection();

private:
    int TSOPPins[TSOP_NUM] = {
        TSOP_1,
        TSOP_2,
        TSOP_3,
        TSOP_4,
        TSOP_5,
        TSOP_6,
        TSOP_7,
        TSOP_8,
        TSOP_9,
        TSOP_10,
        TSOP_11,
        TSOP_12
    };

    int TSOPValues[TSOP_NUM] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
};

#endif

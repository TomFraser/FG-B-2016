#include "TSOPController.h"

TSOPController::TSOPController() {
    for (int i = 0; i < TSOP_NUM; i++) {
        pinMode(TSOPPins[i], INPUT);
    }
}

void TSOPController::updateValues() {
    for (int i = 0; i <= TSOP_NUM; i++) {
		TSOPValues[i] = TSOPValues[i] + (digitalRead(TSOPPins[i]) == HIGH ? 0 : 1);
	}
}

int TSOPController::bestTSOP() {
    bool isZero = true;
    int TSOPNum = 0;
	int bestValue = 0;

	for (int i = 0; i < TSOP_NUM; i++) {
        if (TSOPValues[i] != 0) {
            isZero = false;
        }

		if (TSOPValues[i] > bestValue && TSOPValues[i] < 90) {
			bestValue = TSOPValues[i];
			TSOPNum = i;
		}

		TSOPValues[i] = 0;
	}

    if (isZero) {
        currentTSOP = -1;
    } else {
        currentTSOP = TSOPNum;
    }

    return currentTSOP;
}

int TSOPController::ballDirection() {
    if (currentTSOP == -1) {
        return -1;
    } else {
        return 30 * currentTSOP;
    }
}

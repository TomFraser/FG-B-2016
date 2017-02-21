tsop::tsop(){
    //Nothing Here
}

void tsop::setup(){
    pinMode(TSOP1, INPUT);
    pinMode(TSOP2, INPUT);
    pinMode(TSOP3, INPUT);
    pinMode(TSOP4, INPUT);
    pinMode(TSOP5, INPUT);
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

void tsop::read(){
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

void tsop::copyFilter(){
    //copy
    for (int i = 0; i < SENSORS; i++) {
            tempReadArray[i] = readArray[i];
    }
    //filter TY Team Pi <3
    for (int i = 0; i < SENSORS; i++) {
        if (readArray[i] > MAX_READING || readArray[i] < MIN_READING) {
                    readArray[i] = 0;
        }
    }
}

void tsop::findBest(){
    //Find Best
    bestSensor = 0;
    bestIndex = 0;
    for (int i = 0; i < 21; i++) {
        if (readArray[i] > bestIndex) {
            bestIndex = readArray[i];
        }
    }
    bestSensor = bestIndex;
    return bestSensor;
}

int tsop::average(){
    int oneUp = readArray[bestSensor + 1];
    int oneDown = readArray[bestSensor - 1];
    int originalTSOP = bestSensor;
    float averageTSOP = (oneUp + oneDown + originalTSOP) / 2;
    int averageDegree = averageTSOP * TSOPDegree;
    return averageDegree;
}

void tsop::activate(){
    digitalWrite(TSOP_POWER_PIN, HIGH);

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

    delayMicroseconds(1500);
    digitalWrite(TSOP_POWER_PIN, LOW);
}

void tsop::push(){
    //run this shit when interupted
}

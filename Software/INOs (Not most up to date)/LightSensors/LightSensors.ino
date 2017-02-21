#include <Light.h>

lightSensorZZZ lightPins = {A6, A7, A8, A9, A13, A12, A11, A10, A17, A16, A15, A14, A0, A1, A2, A3};

int reading = 0;

void setup(){

}

void loop(){
    reading = digitalRead(lightPins.one);
    Serial.println(reading);
    reading = 0;
}

struct lightSensorZZZ {
    int one;
    int two;
    int three;
    int four;
    int five;
    int six;
    int seven;
    int eight;
    int nine;
    int ten;
    int eleven;
    int twelve;
    int thirteen;
    int fourteen;
    int fifteen;
    int sixteen;
}

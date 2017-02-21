#include <Light.h>
                       // LEFT, RIGHT, BACK, FRONT
                       //A6, A7, A8, A9, A13, A12, A11, A10, A17, A16, A15, A14, A0, A1, A2, A3
light lightArray = light(A9, A8, A7, A6, A10, A11, A12, A13, A14, A15, A16, A17, A0, A1, A2, A3);

void setup(){
    Serial.begin(9600);
    delay(1000);
}

void loop(){
    Serial.println(analogRead(A1));
    delay(1000);
}

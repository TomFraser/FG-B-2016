void setup(){
    Serial.begin(9600);
}
bool on = false;
//Pin A9
void loop(){
    for(int i = 0; i < 10; i++){
        analogWrite(A9, 255*(i+1));
        blink();
        delay(1000);
        analogWrite(A9, 0);
        delay(1000);
        blink();
    }
}

void blink(){
    if(on){
        digitalWrite(13, LOW);
    }
    else{
        digitalWrite(13, HIGH);
    }
}

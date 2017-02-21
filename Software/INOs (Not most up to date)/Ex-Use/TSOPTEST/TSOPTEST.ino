#define MAX_COUNTER 128
#define SENSORS 20
#define UNLOCK_PIN 27
#define DEBUG_BAUD_RATE 9600
byte sensors[SENSORS] = {0,1,2,3,4,5,6,7,8,9,15,16,17,20,21,22,23,24,25,26};
byte IR_SENSOR = 0;
byte counter = 0;
byte values[SENSORS];

byte b_index = 0;
byte b_value = 0;

void setup() {

  pinMode(UNLOCK_PIN, OUTPUT);
  digitalWrite(UNLOCK_PIN, HIGH);
  for (byte i = 0;i < SENSORS;i++) {
    values[i] = 0;
    pinMode(sensors[i], INPUT);
  }
}

void loop() {
  for (byte i = 0;i < SENSORS;i++) {
    if (sensors[i] < 255) {
      values[i] += (digitalRead(sensors[i]) == HIGH ? 0 : 1);
    }
  }

  counter++;

  if (counter >= MAX_COUNTER) {
    counter = 0;

    for (byte i = 0; i < SENSORS;i++) {
        if(values[i] < 1){
            values[i] = 0;
        }
        if(values[i] < 10){
          values[i] = 0;
        }
      if (values[i] > b_value) {
        b_index = i + 1;
        b_value = values[i];
      }
      values[i] = 0;
    }
  IR_SENSOR = b_index;
    Serial.println(IR_SENSOR);

    counter = 0;

    digitalWrite(UNLOCK_PIN, LOW);
    delay(2);
    digitalWrite(UNLOCK_PIN, HIGH);
  }
}

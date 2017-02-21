#include <LightController.h>

// Motor motorE(5, 8, 9, 32, 0, 1);
// Motor motorF(3, 0, 1, 30, 0, 1);
// Motor motorG(4, 2, 7, 31, 0, 1);
// Motor motorH(6, 24, 25, 33, 0, 1); //PWM, IN1, IN2, SB, Ignore (Standby), Rev



LightController::LightController(int front, int back, int left, int right, int F_threshold, int B_threshold, int L_threshold, int R_threshold){

    // Sensors = Front(A1), Left(A6), Right(A12), Back(A15)

    FrontS = front;
    BackS = back;
    LeftS = left;
    RightS = right;

    Front_T = F_threshold;
    Back_T = B_threshold;
    Left_T = L_threshold;
    Right_T = R_threshold;

    pinMode(FrontS, INPUT);
    pinMode(BackS, INPUT);
    pinMode(RightS, INPUT);
    pinMode(LeftS, INPUT);

    Sensors[0] = FrontS;
    Sensors[1] = BackS;
    Sensors[2] = LeftS;
    Sensors[3] = RightS;

    // Thresholds[0] = analogRead(Sensors[0]) + Front_T; //Front, Back, Left, Right
    // Thresholds[1] = analogRead(Sensors[1]) + Back_T;
    // Thresholds[2] = analogRead(Sensors[2]) + Left_T;
    // Thresholds[3] = analogRead(Sensors[3]) + Right_T;

    for(int i = 0; i < 50; i++){
        Thresholds[0] + analogRead(Sensors[0]);
        Thresholds[1] + analogRead(Sensors[1]);
        Thresholds[2] + analogRead(Sensors[2]);
        Thresholds[3] + analogRead(Sensors[3]);
    }

    Thresholds[0] = Thresholds[0] / 50 + Front_T;
    Thresholds[1] = Thresholds[1] / 50 + Front_T;
    Thresholds[2] = Thresholds[2] / 50 + Front_T;
    Thresholds[3] = Thresholds[3] / 50 + Front_T;

}

void LightController::calibrateLight(int pin){
    if(pin <= 0){
        for(int i = 0; i < 4; i++){
            Serial.println(analogRead(Sensors[i]));
        }
        Serial.println("-------------------");
        delay(1000);
    }
    else{
        if(analogRead(Sensors[3]) > Thresholds[3]){
            Serial.println("TRUE");
        }
        else{
            Serial.println("FALSE");
        }
    }
}

void LightController::calcMultiplier(double runHeading){
    for(int i = 0; i < 4; i++){
        currentReading = analogRead(Sensors[i]);
        if(currentReading >= Thresholds[i]){
            // motorE.set((moveAngles[i][0]) + (runHeading)*2); //Front back left right
            // motorF.set((moveAngles[i][1]) + (runHeading)*2);
            // motorG.set((moveAngles[i][2]) + (runHeading)*2);
            // motorH.set((moveAngles[i][3]) + (runHeading)*2);
            delay(300);
        }
    }
}

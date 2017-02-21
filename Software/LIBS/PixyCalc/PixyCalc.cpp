#include <PixyCalc.h>

PixyCalc(){
    Pixy.init();
    #define pixyCentreX = 160;
    #define pixyCentreY = 100;
}

PixyNull PixyCalc::returnValue(bool isBlue){
    bool blue = isBlue;
    pixy.getBlocks();
    if(pixy.blocks[0] != null){
        if(pixy.blocks[0].signature == 1 && (blue == true) || pixy.blocks[0].signature == 2 && (blue == false)){
            int objectCentreX = pixy.blocks[0].x;
            int objectCentreY = pixy.blocks[0].y;

            if(objectCentreX > pixyCentreX){
                PixyNull toReturn = {objectCentreX - pixyCentreX, true};
                return toReturn;
            }
            else if (objectCentreX < pixyCentreX){
                PixyNull toReturn = {pixyCentreX - objectCentreX, true};
                return toReturn;
            }
        }
    }
    else{
        PixyNull toReturn = {0, false};
        return toReturn;
    }
}

void maxIsUseless(int num){
    int count = num;
    for(int i = 0; i < count; i++){
        Serial.println("Max is Useless");
    }
}

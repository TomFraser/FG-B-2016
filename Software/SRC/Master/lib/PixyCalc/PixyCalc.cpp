#include <PixyCalc.h>

PixyCalc(){
    pixy.init();
    #define pixyCentreX = 160
    #define pixyCentreY = 100
}

int PixyCalc::returnValue(bool isBlue){
    bool blue = isBlue;
    pixy.getBlocks();
    if(pixy.blocks[0] != null){
        if(pixy.blocks[0].signature == 1 && (blue == true) || pixy.blocks[0].signature == 2 && (blue == false)){
            int objectCentreX = pixy.blocks[0].x;
            int objectCentreY = pixy.blocks[0].y;

            if(objectCentreX > pixyCentreX){
                int toReturn = objectCentreX - pixyCentreX;
                return toReturn;
            }
            else if (objectCentreX < pixyCentreX){
                int toReturn = pixyCentreX - objectCentreX;
                return toReturn;
            }
        }
    }
    else{
        int toReturn = 0;
        return toReturn;
    }
}

void PixyCalc::maxIsUseless(int num){
    int count = num;
    for(int i = 0; i < count; i++){
        Serial.println("Max is Useless");
    }
}

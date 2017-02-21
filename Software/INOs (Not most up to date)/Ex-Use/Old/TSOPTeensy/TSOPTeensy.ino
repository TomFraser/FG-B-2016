#include <Tsop.h>

tsop tsopArray = tsop();

void setup(){
    tsopArray.setup();
}

void loop(){
    tsopArray.activate();
    tsopArray.copyFilter();
    tsopArray.findBest();
    tsopArray.push();
}

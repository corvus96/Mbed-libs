#include "main.hpp"

int main(){
    BusOut busCtrl(D8, D7, D4, D2);
    StepperMotor step(busCtrl, 2048);
    RotaryEncoder rotE(D9, D10, 20);
    int angle = 0;
    int currRotAngle = rotE.getPulses()*6;
    double prevRotAngle = currRotAngle;
    while (1) {
        currRotAngle = rotE.getPulses()*6;
        if(currRotAngle != prevRotAngle){
            angle = currRotAngle - prevRotAngle;
            step.rotate(angle, true);
            prevRotAngle = currRotAngle;
            printf("Rotate %d degrees (rotary encoder)\n", rotE.getPulses()*18);
            printf("Rotate %i degrees (stepper motor)\n", angle);
        }
    }

}
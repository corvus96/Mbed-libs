#include "main.hpp"

int main(){
    BusOut busCtrl(D8, D7, D4, D2);
    StepperMotor step(busCtrl, 2048);
    step.rotate(-29, true);
    
}
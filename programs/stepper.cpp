#include "./programs/include/stepper.hpp"
#include <cstdio>

void StepperMotor::rotate(int degrees, bool FullPhase){
    int steps = calculateSteps(degrees); // Convert degrees to steps
    int direction = (degrees > 0) ? 1 : -1; // Positive for clockwise, negative for counter-clockwise
    int i = 0;
    const char *seq = defineSequence(FullPhase, direction);
    int seqSize = (FullPhase) ? 4 : 8; // Full phase sequence is 4 and half phase is 8
    while(i < abs(steps)){
        for(int j = 0; j < seqSize; j++){
            refBusCtrl = seq[j];
            ThisThread::sleep_for(chrono::milliseconds(2));
            //wait_us(int(60000000 / (currentSpeed * stepsPerRevolution))); // Delay based on speed and steps
            i++;
            if(i == abs(steps)) break;
            
        }
    }
}
void StepperMotor::setSpeed(float rpm) {
  if (rpm > 0) {
    currentSpeed = rpm;
  } else {
    currentSpeed = 0.0; // Don't allow negative speeds
  }
}

int StepperMotor::calculateSteps(int degrees){
    int n_steps = static_cast<int>(degrees * (float(stepsPerRev) / 360.0));
    return n_steps;
}

const char* StepperMotor::defineSequence(bool FullPhase, int dir){
    if(dir == 1){
        static const char fullPhaseSeq[] = {0b1000, 0b0100, 0b0010, 0b0001};
        static const char halfPhaseSeq[] = {0b1000, 0b1100, 0b0100, 0b0110, 0b0010, 0b0011, 0b0001, 0b1001};
        return FullPhase ? fullPhaseSeq : halfPhaseSeq;
    }

    static const char fullPhaseSeq[] = {0b0001, 0b0010, 0b0100, 0b1000};
    static const char halfPhaseSeq[] = {0b1001, 0b0001, 0b0011, 0b0010, 0b0110, 0b0100, 0b1100, 0b1000};
    return FullPhase ? fullPhaseSeq : halfPhaseSeq;
}
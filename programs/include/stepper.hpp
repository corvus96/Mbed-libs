#include "mbed.h"

void turn360(int nSpins, int paceWait);

class StepperMotor {
    public:
        StepperMotor(BusOut& busCtrl, int stepsPerRevolution) : refBusCtrl(busCtrl), stepsPerRev(stepsPerRevolution){};
        void setSpeed(float rpm);
        void rotate(int degrees, bool FullPhase = true);
    private:
        BusOut& refBusCtrl;
        int stepsPerRev;
        float currentSpeed = 20;
        int calculateSteps(int degrees);
        const char* defineSequence(bool FullPhase, int dir = 1);
};
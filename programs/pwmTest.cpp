#include "./programs/include/pwmTest.hpp"

AnalogIn ain1(PA_0);
AnalogIn ain2(PA_1);
AnalogIn ain3(PA_4);
PwmOut pwmOut1(PA_9);
PwmOut pwmOut2(PC_7);
PwmOut pwmOut3(PB_6);

void dutyCycleAdjustTest(PinName analogReader, PinName actuator){
    // Initialize pwm pin  and analog reader 
    AnalogIn ain(analogReader);
    PwmOut pwmOut(actuator);
    pwmOut.period(0.0002);
    // Read sensor value
    float dutyPer = ain.read();
    pwmOut.write(dutyPer);
    printf("PWM digital signal dutyper: %i\n",  int(dutyPer*255));
}

void triColorLed(){
    // Initialize pwm pin  and analog reader 
    pwmOut1.period(0.0002);
    pwmOut2.period(0.0002);
    pwmOut3.period(0.0002);
    // Read sensor value
    float dutyPer1 = ain1.read();
    float dutyPer2 = ain2.read();
    float dutyPer3 = ain3.read();
    pwmOut1.write(dutyPer1);
    pwmOut2.write(dutyPer2);
    pwmOut3.write(dutyPer3);
    printf("red: %i\n",  int(dutyPer1*255));
    printf("blue: %i\n",  int(dutyPer2*255));
    printf("green: %i\n",  int(dutyPer3*255));
}

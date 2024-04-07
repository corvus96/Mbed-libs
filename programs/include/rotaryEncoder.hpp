#include "mbed.h"

class RotaryEncoder {
    public:
        bool chA, chB;
        int pulsesPerR;
        RotaryEncoder(PinName channelA, PinName channelB, int pulsesPerRev);
        void set(int pul, int rev);
        void reset(void);
        int getPulses(void);
        int getRev_d();
        double getRev_f();
        double getAngle();
        double getSumangle();
        double getRPM();
    private:
        Timer Mper;
        double RPM;
        InterruptIn channelA_;
        InterruptIn channelB_;
        int          round_rev_d;
        int          prevState_, currState_;
        double angle_, sumangle, round_rev_f;
        int angle_pulses;
        volatile int pulses_;
        volatile int revolutions_;
        void encode();

};
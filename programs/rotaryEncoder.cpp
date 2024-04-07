#include "./programs/include/rotaryEncoder.hpp"

RotaryEncoder::RotaryEncoder(PinName channelA, PinName channelB, int pulsesPerRev) : channelA_(channelA), channelB_(channelB), pulsesPerR(pulsesPerRev){
    pulses_   = 0;
    round_rev_d = 0;
    round_rev_f = 0;

    chA = channelA_.read();
    chB = channelB_.read();

    //2-bit state.
    currState_ = (chA << 1) | (chB);
    prevState_ = currState_;

    channelA_.rise(callback(this, &RotaryEncoder::encode));
    channelA_.fall(callback(this, &RotaryEncoder::encode));
};

void RotaryEncoder::reset(){
    pulses_      = 0;
    round_rev_d = 0;
    round_rev_f = 0;
    sumangle = angle_ =0;
}

void RotaryEncoder::set(int pul, int rev)
{
    pulses_      = pul;
    round_rev_d = rev;
    round_rev_f = rev;
}

int RotaryEncoder::getPulses(void)
{
    return pulses_;
}

int RotaryEncoder::getRev_d()
{
    return round_rev_d;
}

double RotaryEncoder::getRev_f()
{
    return round_rev_f;
}

double RotaryEncoder::getAngle()
{
    return angle_;
}

double RotaryEncoder::getSumangle()
{
    return sumangle;
}

double RotaryEncoder::getRPM()
{
    static double prev_angle;
    Mper.stop();

    RPM = (sumangle - prev_angle) / Mper.read() * 60.0 / 360;
    Mper.reset();
    Mper.start();
    prev_angle = sumangle;
    return RPM;
}



void RotaryEncoder::encode(){
    chA = channelA_.read();
    chB = channelB_.read();
    
    currState_ = (chA << 1) | (chB);
    if ((prevState_ == 0x3 && currState_ == 0x0) ||
            (prevState_ == 0x0 && currState_ == 0x3)) {

        pulses_++;
        angle_pulses++;

    } else if ((prevState_ == 0x2 && currState_ == 0x1) ||
               (prevState_ == 0x1 && currState_ == 0x2)) {

        pulses_--;
        angle_pulses--;

    }
    angle_   = angle_pulses *360/   ((double)pulsesPerR*2);
    sumangle = pulses_      *360/   ((double)pulsesPerR*2);
    round_rev_f = sumangle / 360;
    if(angle_>=360) {
        angle_pulses = angle_ = 0;
        round_rev_d++;
    } else if(angle_<=-360) {
        angle_pulses = angle_ = 0;
        round_rev_d--;
    }
    prevState_ = currState_;
};



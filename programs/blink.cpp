/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "./programs/include/blink.hpp"


// Blinking rate in milliseconds

void blink(Kernel::Clock::duration_u32 rel_time, PinName pin)
{
    // Initialise the digital pin LED1 as an output
    // @param rel_time time delay value
    // @param pin a digital out pin
    DigitalOut led(pin);

    while (true) {
        led = !led;
        ThisThread::sleep_for(rel_time);
    }
}

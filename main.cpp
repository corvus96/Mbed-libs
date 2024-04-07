#include "main.hpp"  

int main() {
  // Initialize bus controller pins for stepper motor control
  BusOut busCtrl(D8, D7, D4, D2);

  // Create a stepper motor object with 2048 steps per revolution
  StepperMotor step(busCtrl, 2048);

  // Create a rotary encoder object connected to pins D9 and D10 with 20 pulses per revolution
  RotaryEncoder rotE(D9, D10, 20);

  // Variables to track angle and encoder readings
  int angle = 0;          // Stores the calculated angle to rotate the stepper motor
  int currRotAngle = rotE.getPulses() * 6;  // Current encoder reading scaled by 6 (adjust if needed)
  double prevRotAngle = currRotAngle;     // Previous encoder reading for comparison

  while (1) {
    // Read the current encoder position and scale by 6 (adjust if needed)
    currRotAngle = rotE.getPulses() * 6;

    // Check if the encoder reading has changed since the last iteration
    if (currRotAngle != prevRotAngle) {
      // Calculate the angle to rotate the stepper motor based on encoder change
      angle = currRotAngle - prevRotAngle;

      step.rotate(angle, true);

      // Update the previous angle reading for future comparisons
      prevRotAngle = currRotAngle;

      // Print the encoder reading converted to degrees 
      printf("Rotate %d degrees (rotary encoder)\n", currRotAngle);

      // Print the actual angle rotated by the stepper motor
      printf("Rotate %i degrees (stepper motor)\n", angle);
    }
  }
}
#include "./programs/include/analogReadTest.hpp"

void analogReadTest(int baudRate,PinName pin){
    // Initialize the analog input pin.
    AnalogIn ain(pin);
    // Initialize the serial port.
    BufferedSerial pc(USBTX, USBRX, baudRate); // USBTX and USBRX are the default serial pins on most mbed boards
    pc.set_format(
        /* bits */ 8,
        /* parity */ BufferedSerial::None,
        /* stop bit */ 1
    );

    // Read the analog value.
    float sensorValue = ain.read();
    int value = round(sensorValue*1023);
    printf("Sensor value: %i\n", value);
    wait_us(100000);
}
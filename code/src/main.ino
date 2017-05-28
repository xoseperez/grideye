#include "config.h"
#include <Wire.h>
#include <SPI.h>
#include <FastLED.h>
#include <MemoryFree.h>

// -----------------------------------------------------------------------------
// HARDWARE
// -----------------------------------------------------------------------------

void i2c_scanner() {

    byte error, address;
    int nDevices;

    nDevices = 0;
    for(address = 1; address < 127; address++ ) {

        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
            SERIAL_PORT.print(F("[I2C] Device found at address 0x"));
            SERIAL_PORT.println(address, HEX);
            nDevices++;
        } else if (error==4) {
            SERIAL_PORT.print(F("[I2C] Unknown error at address 0x"));
            SERIAL_PORT.println(address, HEX);
        }
    }

    if (nDevices == 0) SERIAL_PORT.println(F("[I2C] No devices found"));

}

void freeMem() {
    SERIAL_PORT.print(F("[MAIN] Free memory: "));
    SERIAL_PORT.println(freeMemory());
}

void hardwareSetup() {

    SERIAL_PORT.begin(SERIAL_BAUDRATE);
    SERIAL_PORT.println("[MAIN] Starting");
    freeMem();

    Wire.begin();
    i2c_scanner();

    powerSetup();
    amgSetup();
    buttonSetup();
    #if ENABLE_MATRIX
        matrixSetup();
    #endif
    displaySetup();

}

void writeByte(unsigned char address, unsigned char reg, unsigned char data) {
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
}

unsigned char readByte(unsigned char address, unsigned char reg) {

    unsigned char response = 0;

    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(address, (unsigned char) 1);
    if (1 == Wire.available()) {
        response = Wire.read();
    }

    return response;

}

void readBytes(unsigned char address, unsigned char reg, unsigned char count, unsigned char * dest) {

    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(address, count);

    unsigned char position = 0;
    while (position < count) {
        dest[position++] = Wire.read();
    }

}

// -----------------------------------------------------------------------------
// MAIN
// -----------------------------------------------------------------------------

void setup() {
    hardwareSetup();
}

void loop() {
    buttonLoop();
    amgLoop();
    displayLoop();
}

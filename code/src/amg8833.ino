/*

AMG8833 MODULE

Copyright (C) 2017 by Xose Pérez <xose dot perez at gmail dot com>

*/

#include <Wire.h>

// -----------------------------------------------------------------------------
// AMG8833
// -----------------------------------------------------------------------------

// Status and configuration registers
#define AMG8833_PCTL     0x00
#define AMG8833_RST      0x01
#define AMG8833_FPSC     0x02
#define AMG8833_INTC     0x03
#define AMG8833_STAT     0x04
#define AMG8833_SCLR     0x05
#define AMG8833_AVE      0x07
#define AMG8833_INTHL    0x08
#define AMG8833_INTHH    0x09
#define AMG8833_INTLL    0x0A
#define AMG8833_INTLH    0x0B
#define AMG8833_IHYSL    0x0C
#define AMG8833_IHYSH    0x0D
#define AMG8833_TTHL     0x0E
#define AMG8833_TTHH     0x0F

//  Interrupt result registers
#define AMG8833_INT0     0x10  // threshold interrupt for pixels 0 - 7, etc
#define AMG8833_INT1     0x11
#define AMG8833_INT2     0x12
#define AMG8833_INT3     0x13
#define AMG8833_INT4     0x14
#define AMG8833_INT5     0x15
#define AMG8833_INT6     0x16
#define AMG8833_INT7     0x17

// 64, 16-bit words for the 8 x 8 IR array
#define AMG8833_DATA01L  0x80 // pixel 1 low byte
#define AMG8833_DATA01H  0x81 // pixel 1 high byte
//  ...
#define AMG8833_DATA64L  0xFE // pixel 64 low byte
#define AMG8833_DATA64H  0xFF // pixel 64 high byte

#define AMG8833_ADDRESS 0x68  // 0x68 when ADO = LOW, 0x69 when ADO = HIGH

enum amg8833_mode_t {  // define IR Array operating mode
    NORMAL_MODE = 0,
    SLEEP_MODE,
    STANDBY_MODE_60SEC,
    STANDBY_MODE_10SEC
};

// Define configuration
unsigned char _rawData[128];
float _minTemperature;
float _maxTemperature;
float _avgTemperature;

unsigned int amgThermistor() {
    unsigned char rawData[2] = {0, 0};
    readBytes(AMG8833_ADDRESS, AMG8833_TTHL, 2, &rawData[0]);
    return (unsigned int) (((unsigned int) rawData[1] << 8) | rawData[0]);
}

void amgSetup() {
    writeByte(AMG8833_ADDRESS, AMG8833_RST, 0x3F);  // initialize with a reset
    writeByte(AMG8833_ADDRESS, AMG8833_PCTL, NORMAL_MODE); // set operating mode
    writeByte(AMG8833_ADDRESS, AMG8833_FPSC, 0x00); // sample rate (0x00 = 10 fps or 0x01 = 1 fps)
    SERIAL_PORT.println("[AMG8833] Configured");
}

void amgLoop() {

    static unsigned long last = 0;
    if (millis() - last < AMG8833_UPDATE_INTERVAL) return;
    last = millis();

    //SERIAL_PORT.print("[AMG8833] Thermistor: ");
    //SERIAL_PORT.println(0.0625f * (float) amgThermistor());

    for (unsigned char start=0; start<128; start+=16) {
        readBytes(AMG8833_ADDRESS, AMG8833_DATA01L + start, 16, &_rawData[start]);
    }

    // Calculations
    float min = 1000;
    float max = 0;
    float avg = 0;
    float temperatures[64]; // Contains the calculated temperatures of each pixel in the array
    for (unsigned int i = 0; i < MATRIX_WIDTH * MATRIX_HEIGHT; i++) {
        temperatures[i] = (float) ((_rawData[2*i + 1] << 8) | _rawData[2*i]);
        if (temperatures[i] > 2047) temperatures[i] = temperatures[i] - 4096.0f;
        temperatures[i] *= 0.25f; // scale to get temperatures in degrees C
        avg += temperatures[i];
        if (temperatures[i] > max) max = temperatures[i];
        if (temperatures[i] < min) min = temperatures[i];
    }
    _minTemperature = min;
    _maxTemperature = max;
    avg /= (MATRIX_WIDTH * MATRIX_HEIGHT);
    _avgTemperature = avg;

    // Show matrix
    #if ENABLE_MATRIX
    matrixClear();
    for (int y=0; y<MATRIX_HEIGHT; y++){
        for (int x=0; x<MATRIX_WIDTH; x++){
            CRGB color = getColor(getPattern(), temperatures[y+x*MATRIX_WIDTH], min, max, avg);
            matrixSetPixelColor(x, y, color);
        }
    }
    matrixShow();
    #endif

    //char buffer[64];
    //sprintf(buffer, "[AMG8833] Temperature range: %dC - %dC", (int) min, (int) max);
    //SERIAL_PORT.println(buffer);

}

float amgMinTemperature() {
    return _minTemperature;
}

float amgMaxTemperature() {
    return _maxTemperature;
}

float amgAvgTemperature() {
    return _avgTemperature;
}

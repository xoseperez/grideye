/*

MATRIX MODULE

Copyright (C) 2017 by Xose Pérez <xose dot perez at gmail dot com>

*/

#include <FastLED.h>

#if ENABLE_MATRIX

CRGB _leds[MATRIX_LEDS];

void matrixClear() {
    FastLED.clear();
}

void matrixShow() {
    FastLED.show();
}

void matrixTest() {
    matrixClear();
    for (int i=0; i< MATRIX_LEDS; i++) {
        _leds[i] = CRGB::Red;
        matrixShow();
        delay(200);
    }
}

void matrixAddPixelColor(unsigned int index, CRGB color) {
    if (0 <= index && index < MATRIX_LEDS) {
        _leds[index] += color;
    }
}

void matrixSetPixelColor(unsigned int index, CRGB color) {
    if (0 <= index && index < MATRIX_LEDS) {
        _leds[index] = color;
    }
}

void matrixSetPixelColor(unsigned int x, unsigned int y, CRGB color) {
    if (0 > x || x >= MATRIX_WIDTH) return;
    if (0 > y || y >= MATRIX_HEIGHT) return;
    unsigned int index = matrixGetIndex(x, y);
    _leds[index] = color;
}

unsigned int matrixGetIndex(unsigned int x, unsigned int y) {
    x = MATRIX_WIDTH - x - 1;
    y = MATRIX_HEIGHT - y - 1;
    return x * MATRIX_WIDTH + y;
}

void matrixBrightness(unsigned char brightness) {
    unsigned char b = 16;
    for(unsigned int i=0; i<brightness; i++) b += b;
    FastLED.setBrightness(b);
}

void matrixSetup() {
    FastLED.addLeds<MATRIX_CHIPSET, MATRIX_PIN, MATRIX_COLOR_ORDER>(_leds, MATRIX_LEDS).setCorrection( TypicalLEDStrip );
    matrixBrightness(MATRIX_DEFAULT_BRIGHTNESS);
    SERIAL_PORT.println("[MATRIX] Configured");
}

#endif

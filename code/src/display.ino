/*

SSD1306 MODULE

Copyright (C) 2017 by Xose Pérez <xose dot perez at gmail dot com>

*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// -----------------------------------------------------------------------------
// SSD1306
// -----------------------------------------------------------------------------

Adafruit_SSD1306 display(-1);

void displaySetup() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.clearDisplay();
    display.display();
    SERIAL_PORT.println("[DISPLAY] Configured");
    displayUpdate();
}

void displayOptions(const char * const * options, unsigned char current, unsigned char max) {

    int start = 0;
    int row = 0;
    char buffer[20];

    if (max > 3 && current > 0) start = current - 1;
    for (unsigned char p = start; p < start+3; p++) {

        row += 8;
        if (p >= max) break;
        strcpy_P(buffer, (char*)pgm_read_word(&(options[p])));

        if (p == current) display.setTextColor(BLACK, WHITE);
        display.setCursor(0, row);
        display.println(buffer);
        if (p == current) display.setTextColor(WHITE);

    }

}

void displayUpdate() {

    display.clearDisplay();

    char tmp[10];
    char buffer[20];
    unsigned char state = getState();
    unsigned char pattern = getPattern();

    if (state == STATE_NORMAL) {

        display.setCursor(0, 0);
        strcpy_P(buffer, (char*)pgm_read_word(&(ColorPatternName[pattern])));
        display.println(buffer);

        display.setCursor(84, 0);
        dtostrf(powerRead(), 4, 2, tmp);
        snprintf(buffer, 30, "%sV", tmp);
        display.println(buffer);

        display.setCursor(0, 8);
        dtostrf(amgMinTemperature(), 5, 1, tmp);
        snprintf(buffer, 20, "MINIMUM:     %sC", tmp);
        display.println(buffer);

        display.setCursor(0, 16);
        dtostrf(amgMaxTemperature(), 5, 1, tmp);
        snprintf(buffer, 20, "MAXIMUM:     %sC", tmp);
        display.println(buffer);

        display.setCursor(0, 24);
        dtostrf(amgAvgTemperature(), 5, 1, tmp);
        snprintf(buffer, 20, "AVERAGE:     %sC", tmp);
        display.println(buffer);

    }

    if (state == STATE_PATTERN) {

        display.setCursor(0,0);
        display.println(F("COLOR PATTERN"));

        displayOptions(ColorPatternName, pattern, PATTERN_COUNT);

    }

    if (state == STATE_BRIGHTNESS) {

        display.setCursor(0,0);
        display.println(F("BRIGHTNESS"));

        displayOptions(BrigthnessName, getBrightness(), 3);

    }

    display.display();

}

void displayLoop() {
    static unsigned long last = 0;
    if (millis() - last < DISPLAY_UPDATE_INTERVAL) return;
    last = millis();
    displayUpdate();
}

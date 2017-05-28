/*

PATTERNS MODULE

Copyright (C) 2017 by Xose Pérez <xose dot perez at gmail dot com>

*/

typedef CRGB (* ColorPatternFunction)(float, float, float, float);

// -----------------------------------------------------------------------------
// PATTERNS
// -----------------------------------------------------------------------------

CRGB ColorPatternAveraged(float temperature, float min, float max, float avg) {

    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    g = map(temperature, min, max, 0, 75);

    if (temperature > avg) {
        r = map(temperature, min, max, 0, 255);
    } else if (temperature < avg) {
        b = map(temperature, min, max, 0, 255);
    }

    return CRGB(r, g, b);

}

CRGB ColorPatternHuman(float temperature, float min, float max, float avg) {
    min = 20;
    max = 34; // 31
    avg = 30; // 26
    temperature = constrain(temperature, min, max);
    return ColorPatternAveraged(temperature, min, max, avg);
}

// -----------------------------------------------------------------------------
// SETUP
// -----------------------------------------------------------------------------

ColorPatternFunction colorPattern[PATTERN_COUNT] = {
    &ColorPatternAveraged, // PATTERN_AVERAGED
    &ColorPatternHuman // PATTERN_HUMAN
};

CRGB getColor(unsigned char pattern, float temperature, float min, float max, float avg) {
    if (0 <= pattern && pattern < PATTERN_COUNT) {
        return colorPattern[pattern](temperature, min, max, avg);
    }
    return 0;
}

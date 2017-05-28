/*

STATE MODULE

Copyright (C) 2016-2017 by Xose Pérez <xose dot perez at gmail dot com>

*/

// -----------------------------------------------------------------------------
// STATE
// -----------------------------------------------------------------------------

unsigned char _state = STATE_NORMAL;
unsigned char _pattern = PATTERN_HUMAN;
unsigned char _brightness = 0;

unsigned char getState() {
    return _state;
}

unsigned char getPattern() {
    return _pattern;
}

unsigned char getBrightness() {
    return _brightness;
}

void stateNext() {
    _state = (_state + 1) % STATE_COUNT;
    displayUpdate();
}

void optionNext() {
    if (_state == STATE_PATTERN) {
        _pattern = (_pattern + 1) % PATTERN_COUNT;
    }
    if (_state == STATE_BRIGHTNESS) {
        _brightness = (_brightness + 1) % 3;
        #if ENABLE_MATRIX
        matrixBrightness(_brightness);
        #endif
    }
    displayUpdate();
}

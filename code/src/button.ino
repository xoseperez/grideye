/*

BUTTON MODULE

Copyright (C) 2016-2017 by Xose Pérez <xose dot perez at gmail dot com>

*/

// -----------------------------------------------------------------------------
// BUTTON
// -----------------------------------------------------------------------------

#include <OneButton.h>

OneButton button(BUTTON_PIN, BUTTON_PULLUP);

void buttonClick() {
    SERIAL_PORT.println("[BUTTON] Click");
    optionNext();
}

void buttonDoubleClick() {
    SERIAL_PORT.println("[BUTTON] Double click");
    stateNext();
}

void buttonLongClick() {
    SERIAL_PORT.println("[BUTTON] Long click");
}

void buttonSetup() {
    button.setDebounceTicks(BUTTON_DEBOUNCE_MS);
    button.setClickTicks(BUTTON_DOUBLE_CLICK_MS);
    button.setPressTicks(BUTTON_LONG_CLICK_MS);
    button.attachClick(buttonClick);
    button.attachDoubleClick(buttonDoubleClick);
    button.attachLongPressStop(buttonLongClick);
    SERIAL_PORT.println("[BUTTON] Configured");
}

void buttonLoop() {
    button.tick();
}

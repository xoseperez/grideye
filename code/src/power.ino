/*

POWER MODULE

Copyright (C) 2017 by Xose Pérez <xose dot perez at gmail dot com>

*/

// -----------------------------------------------------------------------------
// BUTTON
// -----------------------------------------------------------------------------

float powerRead() {
    return map(analogRead(POWER_MONITOR_PIN), 0, 1024, 0, 3300) * POWER_MONITOR_RATIO / 1000;
}

void powerSetup() {
    pinMode(POWER_MONITOR_PIN, INPUT);
    SERIAL_PORT.println("[POWER] Configured");
}

//------------------------------------------------------------------------------
// GENERAL
//------------------------------------------------------------------------------

#define SERIAL_PORT                 Serial
#define SERIAL_BAUDRATE             115200

#define ENABLE_MATRIX               1

//--------------------------------------------------------------------------------
// STATES
//--------------------------------------------------------------------------------

#define STATE_NORMAL                0
#define STATE_PATTERN               1
#define STATE_BRIGHTNESS            2
#define STATE_COUNT                 3

//--------------------------------------------------------------------------------
// AMG8833
//--------------------------------------------------------------------------------

// Max refresh update for the AMG8833 is 10Hz as per datasheet (100ms)
#define AMG8833_UPDATE_INTERVAL     100

//--------------------------------------------------------------------------------
// POWER
//--------------------------------------------------------------------------------

#define POWER_MONITOR_PIN           A0
#define POWER_MONITOR_RATIO         2.0

//--------------------------------------------------------------------------------
// MATRIX
//--------------------------------------------------------------------------------

#define MATRIX_PIN                  4
#define MATRIX_WIDTH                8
#define MATRIX_HEIGHT               8
#define MATRIX_CHIPSET              WS2812B
#define MATRIX_COLOR_ORDER          GRB
#define MATRIX_LEDS                 (MATRIX_WIDTH * MATRIX_HEIGHT)
#define MATRIX_DEFAULT_BRIGHTNESS   0

const char brightness_low[] PROGMEM = "LOW";
const char brightness_medium[] PROGMEM = "MEDIUM";
const char brightness_high[] PROGMEM = "HIGH";
const char * const BrigthnessName[] PROGMEM = {
    brightness_low,
    brightness_medium,
    brightness_high
};


//--------------------------------------------------------------------------------
// BUTTON
//--------------------------------------------------------------------------------

#define BUTTON_PIN                  9
#define BUTTON_PULLUP               1
#define BUTTON_DEBOUNCE_MS          20
#define BUTTON_DOUBLE_CLICK_MS      300
#define BUTTON_LONG_CLICK_MS        500

//--------------------------------------------------------------------------------
// DISPLAY
//--------------------------------------------------------------------------------

#define DISPLAY_UPDATE_INTERVAL     1000

//--------------------------------------------------------------------------------
// COLOR PATTERNS
//--------------------------------------------------------------------------------

#define PATTERN_AVERAGED            0
#define PATTERN_HUMAN               1
#define PATTERN_COUNT               2

const char pattern_averaged[] PROGMEM = "AVERAGED";
const char pattern_human[] PROGMEM = "HUMAN";
const char * const ColorPatternName[] PROGMEM = {
    pattern_averaged,
    pattern_human
};

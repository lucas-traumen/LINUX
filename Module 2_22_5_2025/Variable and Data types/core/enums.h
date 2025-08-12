#ifndef ENUMS_H
#define ENUMS_H

typedef enum {
    MODE_AUTO,
    MODE_MANUAL
} SystemMode;

typedef enum {
    PUMP_OFF,
    PUMP_ON
} PumpState;

typedef enum {
    LED_NORMAL,
    LED_WATERING,
    LED_LOW_MOISTURE_ALERT,
    LED_ERROR
} LedStatus;

#endif
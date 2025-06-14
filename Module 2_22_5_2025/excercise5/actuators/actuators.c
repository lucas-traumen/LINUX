#include <stdio.h>
#include "actuators.h"

void turn_pump_on(SystemState* state) {
    state->pump = PUMP_ON;
    printf("[Pump] ON\n");
}

void turn_pump_off(SystemState* state) {
    state->pump = PUMP_OFF;
    printf("[Pump] OFF\n");
}

void update_led(LedStatus led) {
    const char* msg[] = {"Green", "Yellow", "Red", "ERROR"};
    printf("[LED] Status: %s\n", msg[led]);
}
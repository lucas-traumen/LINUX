#include<stdio.h>
#include"watering.h"

void process_logic(SystemState* state, SensorData data) {
    if (state->mode == MODE_AUTO) {
        if (data.soilMoisture < state->moistureMin) {
            turn_pump_on(state);
            update_led(LED_WATERING);
        } else if (data.soilMoisture >= state->moistureMax) {
            turn_pump_off(state);
            update_led(LED_NORMAL);
        }
    }
}
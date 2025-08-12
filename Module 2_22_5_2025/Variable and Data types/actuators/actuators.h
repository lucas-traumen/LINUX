#ifndef ACTUATORS_H
#define ACTUATORS_H

#include "../core/data.h"

void turn_pump_on(SystemState* state);
void turn_pump_off(SystemState* state);
void update_led(LedStatus led);


#endif
#ifndef WATERING_H
#define WATERING_H


#include "../core/data.h"
#include "../config/config.h"
#include "../core/enums.h"
#include "../actuators/actuators.h"


void process_logic(SystemState* state, SensorData data);

#endif
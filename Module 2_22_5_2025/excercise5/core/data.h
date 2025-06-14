#ifndef DATA_H
#define DATA_H
#include "../core/enums.h"

typedef struct {
    int soilMoisture;
    int temperature;
} SensorData;

typedef struct {
    SystemMode mode;
    PumpState pump;
    LedStatus led;
    int moistureMin;
    int moistureMax;
    int wateringDuration;
} SystemState;

#endif
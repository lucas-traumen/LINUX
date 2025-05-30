#ifndef SENSOR_FACTORY_H
#define SENSOR_FACTORY_H

#include "sensor.h"

// Enum to represent sensor types
typedef enum {
    SENSOR_TEMPERATURE,
    SENSOR_HUMIDITY,
    SENSOR_LIGHT,
    SENSOR_ATMOSPHERE
} SensorType;

// Factory method to create sensors based on their type
Sensor* createSensor(SensorType type);

#endif


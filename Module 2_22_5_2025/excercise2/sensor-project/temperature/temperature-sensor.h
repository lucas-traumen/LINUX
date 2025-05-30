#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include "../sensor-factory/sensor.h"

// Function prototypes for the temperature sensor
void temperatureSensorInit();
float temperatureSensorReadData();
Sensor createTemperatureSensor();

#endif
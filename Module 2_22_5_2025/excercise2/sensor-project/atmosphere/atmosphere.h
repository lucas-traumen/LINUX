#ifndef ATMOSPHERE_SENSOR_H
#define ATMOSPHERE_SENSOR_H

#include "../sensor-factory/sensor.h"

// Function prototypes for the humidity sensor
void  atmosphereSensorInit();
float  atmosphereSensorReadData();
Sensor createAtmosphereSensor();

#endif

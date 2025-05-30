#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include "../sensor-factory/sensor.h"

// Function prototypes for the light sensor
void lightSensorInit();
float lightSensorReadData();
Sensor createLightSensor();

#endif

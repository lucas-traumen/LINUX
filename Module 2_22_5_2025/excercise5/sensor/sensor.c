#include <stdio.h>
#include <stdlib.h> // for rand()
#include "sensor.h"

SensorData read_sensors(void) {
SensorData data;
data.soilMoisture = rand() % 101; // Simulated 0-100%
data.temperature = 25 + rand() % 6; // Simulated 25-30°C
printf("[Sensor] Moisture: %d%%, Temp: %d°C\n", data.soilMoisture, data.temperature);
return data;
}
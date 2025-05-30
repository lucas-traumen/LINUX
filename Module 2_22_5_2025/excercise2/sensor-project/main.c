#include <stdio.h>
#include <stdlib.h>
#include "sensor-factory/sensor-factory.h"

int main() {
    // Create a temperature sensor
    Sensor* tempSensor = createSensor(SENSOR_TEMPERATURE);
    if (tempSensor != NULL) {
        tempSensor->init();
        printf("Temperature: %.2f°C\n", tempSensor->readData());
        free(tempSensor);
    }

    // Create a humidity sensor
    Sensor* humiditySensor = createSensor(SENSOR_HUMIDITY);
    if (humiditySensor != NULL) {
        humiditySensor->init();
        printf("Humidity: %.2f%%\n", humiditySensor->readData());
        free(humiditySensor);
    }

    // Create a light sensor
    Sensor* lightSensor = createSensor(SENSOR_LIGHT);
    if (lightSensor != NULL) {
        lightSensor->init();
        printf("Light Intensity: %.2f lux\n", lightSensor->readData());
        free(lightSensor);
    }
    
    // Create a atmosphere sensor
    Sensor* atmosphereSensor = createSensor(SENSOR_ATMOSPHERE);
    if (atmosphereSensor != NULL) {
        atmosphereSensor->init();
        printf("Atmosphere measuare : %.2f atm\n", atmosphereSensor->readData());
        free(atmosphereSensor);
    }
    return 0;
}

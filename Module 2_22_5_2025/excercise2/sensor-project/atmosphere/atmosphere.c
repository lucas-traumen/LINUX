#include <stdio.h>
#include "atmosphere.h"

// Initialize the atmosphere sensor
void atmosphereSensorInit() {
    printf("Atmosphere sensor initialized.\n");
}

// Read data from the atmosphere sensor
float atmosphereSensorReadData() {
    return 1.0; // Simulated value
}

// Create a atmosphere sensor object
Sensor createAtmosphereSensor() {
    Sensor atmosphereSensor;
    atmosphereSensor.init = atmosphereSensorInit;
    atmosphereSensor.readData = atmosphereSensorReadData;
    return atmosphereSensor;
}
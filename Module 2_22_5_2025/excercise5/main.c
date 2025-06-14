#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "core/data.h"
#include "config/config.h"
#include "sensor/sensor.h"
#include "actuators/actuators.h"
#include "buttons/buttons.h"
#include "watering_logic/watering.h"

int main() {
    SystemState system = {
        .mode = MODE_AUTO,
        .pump = PUMP_OFF,
        .led = LED_NORMAL,
        .moistureMin = MOISTURE_MIN_THRESHOLD,
        .moistureMax = MOISTURE_MAX_THRESHOLD,
        .wateringDuration = WATERING_DURATION
    };

    while (1) {
        // Simulate button press
        if (read_button_auto_toggle()) {
            system.mode = (system.mode == MODE_AUTO) ? MODE_MANUAL : MODE_AUTO;
            printf("[Mode] Switched to: %s\n", system.mode == MODE_AUTO ? "AUTO" : "MANUAL");
        }
        if (read_button_manual_water() && system.mode == MODE_MANUAL) {
            turn_pump_on(&system);
            update_led(LED_WATERING);
            sleep(system.wateringDuration);
            turn_pump_off(&system);
        }

        SensorData sensor = read_sensors();
        process_logic(&system, sensor);
        sleep(SENSOR_CHECK_INTERVAL); // Wait for next check
    }
    return 0;
}

#include<stdio.h>
#include"watering.h"

 void process_logic(SystemState* state, SensorData data) {
    if (state->mode == MODE_AUTO) {
           // Kiểm tra lỗi cảm biến (ví dụ dữ liệu âm là lỗi mô phỏng)
        if (data.soilMoisture < 0 || data.temperature < 0) {
            turn_pump_off(state);
            update_led(LED_ERROR);  // LED đỏ báo lỗi
            printf("[Error] Sensor data invalid.\n");
            return;
        }

        // Cảnh báo: đất khô nhưng chưa đến ngưỡng tưới → LED đỏ (cảnh báo thấp)
        else if (data.soilMoisture < state->moistureMin - 5 && state->pump == PUMP_OFF) {
            update_led(LED_LOW_MOISTURE_ALERT);  // LED đỏ cảnh báo
        }

        // Điều kiện tưới nước
        else if (data.soilMoisture < state->moistureMin) {
            turn_pump_on(state);
            update_led(LED_WATERING);  // LED vàng
        }
        // Đủ ẩm → tắt bơm
        else if (data.soilMoisture >= state->moistureMax) {
            turn_pump_off(state);
            update_led(LED_NORMAL);  // LED xanh
        }


    }
}
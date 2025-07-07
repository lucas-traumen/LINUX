#include <stdio.h>
#include "led_driver.h"



void print_led_buffer() {
    const uint32_t* buffer = led_get_buffer();
    size_t count = led_get_pixel_count();
    printf("LED Buffer:\n");
    for (size_t i = 0; i < count; i++) {
        printf("Pixel %zu: 0x%06X\n", i, buffer[i] & 0xFFFFFF);
    }
    printf("\n");
}

int main() {
    if (led_init(5) != 0) {
        printf("Failed to initialize LED buffer.\n");
        return ERROR_MEMORY_ALLOC;
    }

    led_set_pixel_color(0, 255, 0, 0);     // Red
    led_set_pixel_color(1, 0, 255, 0);     // Green
    led_set_pixel_color(2, 0, 0, 255);     // Blue
    led_set_pixel_color(3, 255, 255, 0);   // Yellow
    led_set_pixel_color(4, 255, 255, 255); // White

    print_led_buffer();

    led_fill(128, 0, 128); // Purple
    print_led_buffer();

    led_clear(); // Turn off all
    print_led_buffer();

    led_shutdown();
    return 0;
}

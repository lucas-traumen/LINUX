#include "led_driver.h"
#include <stdlib.h>
#include <string.h>

static uint32_t* led_buffer = NULL;
static size_t pixel_count = 0;

int led_init(size_t num_pixels) {
    if (num_pixels == 0) return FAIL_INITIAL ;

    led_buffer = (uint32_t*)malloc(sizeof(uint32_t) * num_pixels);
    if (!led_buffer) return ERROR_MEMORY_ALLOC ;

    pixel_count = num_pixels;
    led_clear(); // Set all LEDs to black initially
    return 0;
}

void led_shutdown() {
    free(led_buffer);
    led_buffer = NULL; // avoid Darling pointer 
    pixel_count = 0;
}

void led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b) {
    if (!led_buffer || index >= pixel_count) return;

    // G-R-B format packed into 24 bits, top 8 bits are zero
    led_buffer[index] = ((uint32_t)g << 16) | ((uint32_t)r << 8) | b;
}

void led_fill(uint8_t r, uint8_t g, uint8_t b) {
    if (!led_buffer) return;

    uint32_t color = ((uint32_t)g << 16) | ((uint32_t)r << 8) | b;
    for (size_t i = 0; i < pixel_count; i++) {
        led_buffer[i] = color;
    }
}

void led_clear() {
    if (led_buffer) {
        memset(led_buffer, 0, sizeof(uint32_t) * pixel_count);
    }
}

const uint32_t* led_get_buffer() {
    return led_buffer;
}

size_t led_get_pixel_count() {
    return pixel_count;
}



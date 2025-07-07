#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>
#include <stddef.h>

#define ERROR_MEMORY_ALLOC -1
#define FAIL_INITIAL       -1

int led_init(size_t num_pixels);
void led_shutdown();

void led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b);
void led_fill(uint8_t r, uint8_t g, uint8_t b);
void led_clear();

const uint32_t* led_get_buffer();
size_t led_get_pixel_count();

#endif // LED_DRIVER_H
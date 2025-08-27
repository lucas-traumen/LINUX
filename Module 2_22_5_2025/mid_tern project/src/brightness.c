#include "brightness.h"
#include <stdlib.h>

static int brightness_getStatus(void) {
    int level = rand() % 100;
    return (level < 10) ? 1 : 0; // warning nếu quá tối
}

Subsystem Brightness = {
    .name = "Brightness",
    .getStatus = brightness_getStatus
    
};

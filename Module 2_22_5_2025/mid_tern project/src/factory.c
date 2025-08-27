#include "factory.h"

// các subsystem được định nghĩa bên ngoài (ở các .c file riêng)
extern Subsystem CPU;
extern Subsystem RAM;
extern Subsystem ROM;
extern Subsystem Brightness;
extern Subsystem Network;
extern Subsystem System;
// extern Subsystem Storage;
// extern Subsystem Temperature;

Subsystem* createSubsystem(SubsystemType type) {
    switch(type) {
        case SUBSYSTEM_CPU:         return &CPU;
        case SUBSYSTEM_RAM:         return &RAM;
        case SUBSYSTEM_ROM:         return &ROM;
        case SUBSYSTEM_BRIGHTNESS:  return &Brightness;
        case SUBSYSTEM_NETWORK:     return &Network;
        case SUBSYSTEM_KERNEL:     return &System;
        // case SUBSYSTEM_STORAGE:     return &Storage;
        // case SUBSYSTEM_TEMPERATURE: return &Temperature;
        default: return NULL;
    }
}

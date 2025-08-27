#ifndef FACTORY_H
#define FACTORY_H
#include "subsystem.h"
#include <stdio.h>
typedef enum {
    SUBSYSTEM_CPU,
    SUBSYSTEM_RAM,
    SUBSYSTEM_ROM,
    SUBSYSTEM_BRIGHTNESS,
    SUBSYSTEM_NETWORK,
    SUBSYSTEM_KERNEL
    
} SubsystemType;

Subsystem* createSubsystem(SubsystemType type);

#endif

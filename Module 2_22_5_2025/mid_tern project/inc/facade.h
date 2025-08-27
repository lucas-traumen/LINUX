#ifndef FACADE_H
#define FACADE_H
#include "subsystem.h"

typedef struct {
    Subsystem* subsystems[8];
    int subsystemCount;
    void (*checkHealth)(void);
} SystemMonitorFacade;

SystemMonitorFacade* getSystemMonitor(void);

#endif

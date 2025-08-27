#include "facade.h"
#include "factory.h"
#include "logger.h"

static void checkHealth(void) {
    Logger* log = getLoggerInstance();
    for (int i = 0; i < 6; i++) {
        Subsystem* s = createSubsystem(i);
        int status = s->getStatus();
        if (status == 0)
            log->log(LOG_INFO, "%s OK", s->name);
        else if (status == 1)
            log->log(LOG_WARNING, "%s Warning", s->name);
        else
            log->log(LOG_ERROR, "%s Error", s->name);
    }
}

SystemMonitorFacade* getSystemMonitor(void) {
    static SystemMonitorFacade monitor = {
        .checkHealth = checkHealth
    };
    return &monitor;
}

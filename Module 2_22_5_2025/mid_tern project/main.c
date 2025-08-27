#include "./inc/logger.h"
#include "./inc/buzzer.h"
#include "./inc/facade.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>

]


int main() {
    int i=10;
    while(i)
    {
        Logger *logger = getLoggerInstance();
        setLogLevel(LOG_DEBUG);
        SystemMonitorFacade *monitor = getSystemMonitor();
        monitor->checkHealth();
        sleep(1);
        i--;
    }
    


    
    return 0;
}
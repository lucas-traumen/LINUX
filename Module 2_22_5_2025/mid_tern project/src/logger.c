#include "logger.h"
#include <stdlib.h>

static Logger *singletonLogger = NULL;
static char buffer[LOG_BUFFER_SIZE];

static void get_timestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}

static void logMessage(LogLevel level, const char *format, ...) {
    if (!singletonLogger || level > singletonLogger->currentLogLevel) return;

    const char *logLevelNames[] = {
        "EMERGENCY", "ALERT", "CRITICAL", "ERROR",
        "WARNING", "NOTICE", "INFO", "DEBUG"
    };

    char timestamp[20];
    get_timestamp(timestamp, sizeof(timestamp));
    fprintf(singletonLogger->logFile,"[%s][%s] ",timestamp,logLevelNames[level]);
    va_list args;
    va_start(args, format);
    vfprintf(singletonLogger->logFile,format, args);
    va_end(args);
    fprintf(singletonLogger->logFile,"\n");
}

void checkThresholds(size_t currentRAM, size_t currentStorage) {
    if (!singletonLogger) return;

    if (currentRAM > singletonLogger->ramThreshold_bytes) {
        singletonLogger->log(LOG_WARNING, "RAM usage exceeded threshold: %zu bytes", currentRAM);
        buzzer_beep_ms(singletonLogger->logFile,1000);
    }

    if (currentStorage > singletonLogger->storageThreshold_bytes) {
        singletonLogger->log(LOG_WARNING, "Storage usage exceeded threshold: %zu bytes", currentStorage);
        buzzer_beep_ms(singletonLogger->logFile,1000);
    }
} 
void setThresholds(size_t ram, size_t storage) {
    if (!singletonLogger) return;
    singletonLogger->ramThreshold_bytes = ram;
    singletonLogger->storageThreshold_bytes = storage;
}

Logger *getLoggerInstance(void) {
    if (singletonLogger ==NULL) {
        singletonLogger = malloc(sizeof(Logger));
        singletonLogger->logFile = fopen("app_log.txt","a");
        if (!singletonLogger->logFile) {
            free(singletonLogger);
            exit(EXIT_FAILURE);
        }
        singletonLogger->currentLogLevel = LOG_DEBUG;
        singletonLogger->ramThreshold_bytes = 0;
        singletonLogger->storageThreshold_bytes = 0;
        singletonLogger->log = logMessage;
        singletonLogger->checkThresholds = checkThresholds;
        singletonLogger->setThresholds = setThresholds;
        if (singletonLogger->logFile && LOG_BUFFER_SIZE > 0){
            setvbuf(singletonLogger->logFile,buffer,_IOFBF,LOG_BUFFER_SIZE);
        }
    }
    return singletonLogger;
}

void setLogLevel(LogLevel level) {
    if (singletonLogger) singletonLogger->currentLogLevel = level;
}

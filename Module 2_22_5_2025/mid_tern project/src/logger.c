#include "logger.h"
#include <stdlib.h>

static Logger *singletonLogger = NULL;
static char buffer[LOG_BUFFER_SIZE_BYTES];

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

// void checkThresholds(size_t currentRAM, size_t currentStorage, int cpuUsage, int voltage, int temperature) {
//     if (cpuUsage > singletonLogger->cpuUsageThreshold_percent) {
//         singletonLogger->log(LOG_WARNING, "CPU usage exceeded: %d%%", cpuUsage);
//         buzzer_beep_ms(singletonLogger->logFile, 500);
//     }
//     if (currentRAM < singletonLogger->ramThreshold_bytes) {
//         singletonLogger->log(LOG_WARNING, "Low RAM: %zu bytes left", currentRAM);
//         buzzer_beep_ms(singletonLogger->logFile, 500);
//     }
//     if (voltage < singletonLogger->voltageThreshold_mV) {
//         singletonLogger->log(LOG_ERROR, "Voltage low: %dmV", voltage);
//         buzzer_beep_ms(singletonLogger->logFile, 1000);
//     }
//     if (temperature > singletonLogger->temperatureThreshold_C) {
//         singletonLogger->log(LOG_CRITICAL, "Overheat: %d °C", temperature);
//         buzzer_beep_ms(singletonLogger->logFile, 1500);
//     }
// }
// void setThresholds(size_t ram, size_t storage, int cpu_precent, int voltage, int temprature ) {
//     if (singletonLogger == NULL) return; 
//     singletonLogger->ramThreshold_bytes = ram;
//     singletonLogger->storageThreshold_bytes = storage;
//     singletonLogger->cpuUsageThreshold_percent = cpu_precent;
//     singletonLogger->voltageThreshold_mV = voltage;
//     singletonLogger->temperatureThreshold_C = temprature;
// }

Logger *getLoggerInstance(void) {
    if (singletonLogger ==NULL) {
        singletonLogger = malloc(sizeof(Logger));
        singletonLogger->logFile = fopen("app_log.txt","a");
        if (!singletonLogger->logFile) {
            free(singletonLogger);
            exit(EXIT_FAILURE);
        }
        
        if (singletonLogger->logFile && LOG_BUFFER_SIZE_BYTES > 0){
            setvbuf(singletonLogger->logFile,buffer,_IOFBF,LOG_BUFFER_SIZE_BYTES);
        }
    }
    singletonLogger->log = logMessage;
    singletonLogger->currentLogLevel = LOG_DEBUG;  
    return singletonLogger;
}

void setLogLevel(LogLevel level) {
    if (singletonLogger) singletonLogger->currentLogLevel = level;
}

// logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>
#include "buzzer.h"

#define LOG_BUFFER_SIZE_BYTES   65536

typedef enum {
    LOG_EMERGENCY = 0,
    LOG_ALERT,
    LOG_CRITICAL,
    LOG_ERROR,
    LOG_WARNING,
    LOG_NOTICE,
    LOG_INFO,
    LOG_DEBUG
} LogLevel;

typedef struct {
    FILE *logFile;
    LogLevel currentLogLevel;
    size_t ramThreshold_bytes;
    size_t storageThreshold_bytes;
    int cpuUsageThreshold_percent;
    int voltageThreshold_mV;
    int temperatureThreshold_C;  
    void (*log)(LogLevel, const char*, ...);
    // Methods
    void (*checkThresholds)(size_t currentRAM, size_t currentStorage, int cpuUsage, int voltage, int temperature);
    void (*setThresholds)(size_t ram, size_t storage, int cpuUsage, int voltage, int temperature);
} Logger;

Logger *getLoggerInstance(void);
void setLogLevel(LogLevel level);

#endif

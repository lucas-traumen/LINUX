// logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>
#include "buzzer.h"

#define LOG_BUFFER_SIZE    65536

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
    void (*log)(LogLevel, const char*, ...);
    void (*checkThresholds)(size_t currentRAM, size_t currentStorage);
    void (*setThresholds)(size_t ram, size_t storage);
} Logger;

Logger *getLoggerInstance(void);
void setLogLevel(LogLevel level);

#endif

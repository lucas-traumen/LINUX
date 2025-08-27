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
    void (*log)(LogLevel, const char*, ...);
} Logger;

Logger *getLoggerInstance(void);
void setLogLevel(LogLevel level);

#endif

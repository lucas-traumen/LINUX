#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#define ERROR_INITIALATION -1
// Log levels based on syslog
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

// Initialize logger
int logger_init(const char *log_filename, LogLevel level);

// Shutdown logger
void logger_shutdown();

// Change log level at runtime
void logger_set_level(LogLevel level);

// Core logging function
void logger_log(LogLevel level, const char *file, int line, const char *fmt, ...);

// User-friendly macro
#define log_message(level, fmt, ...) \
    logger_log(level, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#endif



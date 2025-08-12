#include "logger.h"
#include <stdlib.h>
#include <string.h>

static FILE *log_file = NULL;
static LogLevel current_level = LOG_INFO;

static const char *level_to_string(LogLevel level) {
    static const char *levels[] = {
        "EMERGENCY", "ALERT", "CRITICAL", "ERROR",
        "WARNING", "NOTICE", "INFO", "DEBUG"
    };
    return (level >= 0 && level <= LOG_DEBUG) ? levels[level] : "UNKNOWN";
}

static void get_timestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}

int logger_init(const char *log_filename, LogLevel level) {
    current_level = level;
    if (log_filename) {
        log_file = fopen(log_filename, "a");
        if (!log_file) return ERROR_INITIALATION;
    }
    return 0;   
}

void logger_shutdown() {
    if (log_file) {
        fclose(log_file);
        log_file = NULL;
    }
}

void logger_set_level(LogLevel level) {
    current_level = level;
}

void logger_log(LogLevel level, const char *file, int line, const char *fmt, ...) {
    if (level > current_level) return;

    char timestamp[20];
    get_timestamp(timestamp, sizeof(timestamp));

    char message[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(message, sizeof(message), fmt, args);
    va_end(args);

    char output[1200];
    snprintf(output, sizeof(output), "[%s] [%s] [%s:%d] - %s\n",
             timestamp, level_to_string(level), file, line, message);

    // Console output
    FILE *out = (level <= LOG_ERROR) ? stderr : stdout;
    fputs(output, out);
    fflush(out);

    // File output
    if (log_file) {
        fputs(output, log_file);
        fflush(log_file);
    }
}
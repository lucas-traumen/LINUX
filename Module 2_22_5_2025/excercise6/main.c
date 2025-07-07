#include "logger.h"

int main() {
    if (logger_init("app.log", LOG_DEBUG) != 0) {
        fprintf(stderr, "Failed to initialize logger.\n");
        return 1;
    }

    log_message(LOG_INFO, "Application started.");
    log_message(LOG_WARNING, "This is a warning.");
    log_message(LOG_ERROR, "An error occurred: %s", "connection failed");
    log_message(LOG_DEBUG, "Debug details: x = %d", 42);

    logger_set_level(LOG_ERROR);
    log_message(LOG_DEBUG, "This should be filtered out.");
    log_message(LOG_CRITICAL, "Critical failure!");

    logger_shutdown();
    return 0;
}

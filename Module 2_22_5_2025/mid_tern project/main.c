#include "./inc/logger.h"
#include "./inc/buzzer.h"
#include<stdio.h>
#include <unistd.h>

#define RAM 100
#define STORAGE 10000
#define RAM_CURRENT 101
#define STORAGE_CURRENT 10001

int main() {
    // Get the singleton logger instance
    Logger *logger = getLoggerInstance();

    // Set log level to WARNING
    setLogLevel(LOG_WARNING);

    // Log messages of different levels
    logger->log(LOG_EMERGENCY, "This is an emergency message.");
    logger->log(LOG_ALERT, "This is an alert message.");
    logger->log(LOG_CRITICAL, "This is a critical message.");
    logger->log(LOG_ERROR, "This is an error message.");
    logger->log(LOG_WARNING, "This is a warning message.");
    logger->log(LOG_NOTICE, "This is a notice message.");
    logger->log(LOG_DEBUG, "This is a debug message.");

    logger->setThresholds(RAM,STORAGE);
    sleep(3);
    logger->checkThresholds(RAM,STORAGE);
    sleep(3);
    logger->checkThresholds(RAM_CURRENT,STORAGE_CURRENT);
    
    
    return 0;
}
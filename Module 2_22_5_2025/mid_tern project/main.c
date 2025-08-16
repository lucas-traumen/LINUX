#include "./inc/logger.h"
#include "./inc/buzzer.h"
#include<stdio.h>
#include <unistd.h>

#define RAM_LOW_THRESHOLD_BYTES       1024
#define STORAGE_LOW_THRESHOLD_BYTES   2048
#define CPU_USAGE_THRESHOLD_PERCENT   80
#define VOLT_LOW_THRESHOLD_MILLIVOLT  3000
#define TEMP_HIGH_THRESHOLD_C         70


int main() {
    Logger *logger = getLoggerInstance();
    setLogLevel(LOG_DEBUG);
    int voltage =2500;
    int temp =90;
    
    logger->log(LOG_EMERGENCY, "System is unusable! Shutting down...");
    logger->log(LOG_ALERT, "Immediate action required: Overcurrent detected");
    logger->log(LOG_CRITICAL, "Critical failure in power supply");
    logger->log(LOG_ERROR, "Voltage critical: %dmV", voltage);
    logger->log(LOG_WARNING, "Temperature high: %d C", temp);
    logger->log(LOG_NOTICE, "Network interface restarted");
    logger->log(LOG_INFO, "System boot OK");
    logger->log(LOG_DEBUG, "ADC raw value = %d", 1234);

    logger->setThresholds(RAM_LOW_THRESHOLD_BYTES,STORAGE_LOW_THRESHOLD_BYTES,CPU_USAGE_THRESHOLD_PERCENT,VOLT_LOW_THRESHOLD_MILLIVOLT,TEMP_HIGH_THRESHOLD_C);
    sleep(3);
    logger->checkThresholds(512,1024,60,4000,70);
    sleep(3);
    logger->checkThresholds(2048,3000,90,1500,95);
    
    
    return 0;
}
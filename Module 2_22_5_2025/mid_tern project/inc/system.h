#ifndef SYSTEM_H
#define SYSTEM_H

#include "logger.h"
#include "subsystem.h"
#include "factory.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    double uptime_seconds;          // thời gian chạy từ lúc boot
    char   sys_time[64];            // thời gian hiện tại
    char   kernel_version[256];     // phiên bản kernel
    char   running_services[4096];  // danh sách service đang chạy
} SystemManager;

SystemManager* system_manager_create(void);
void system_manager_destroy(SystemManager* sm);

void get_system_uptime(SystemManager* sm);
void get_system_time(SystemManager* sm);
void get_kernel_version(SystemManager* sm);
void get_running_services(SystemManager* sm);

#ifdef __cplusplus
}
#endif

#endif // SYSTEM_H

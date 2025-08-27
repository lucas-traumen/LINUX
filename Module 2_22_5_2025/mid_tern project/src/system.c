#include <stdio.h>
#include <stdlib.h>
#include "system.h"
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/utsname.h>

SystemManager* system_manager_create(void) {
    SystemManager* sm = (SystemManager*)malloc(sizeof(SystemManager));
    if (!sm) return NULL;
    memset(sm, 0, sizeof(SystemManager));
    return sm;
}

void system_manager_destroy(SystemManager* sm) {
    if (sm) free(sm);
}

void get_system_uptime(SystemManager* sm) {
    FILE* f = fopen("/proc/uptime", "r");
    if (f) {
        fscanf(f, "%lf", &sm->uptime_seconds);
        fclose(f);
    }
}

void get_system_time(SystemManager* sm) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    strftime(sm->sys_time, sizeof(sm->sys_time), "%Y-%m-%d %H:%M:%S", t);
}

void get_kernel_version(SystemManager* sm) {
    struct utsname uts;
    if (uname(&uts) == 0) {
        snprintf(sm->kernel_version, sizeof(sm->kernel_version),
                 "%s %s", uts.sysname, uts.release);
    }
}

void get_running_services(SystemManager* sm) {
    FILE* f = popen("systemctl list-units --type=service --state=running --no-pager --no-legend", "r");
    if (!f) return;
    char buf[256];
    while (fgets(buf, sizeof(buf), f)) {
        strncat(sm->running_services, buf, sizeof(sm->running_services)-strlen(sm->running_services)-1);
    }
    pclose(f);
}

static int system_getStatus(void) {
    SystemManager* sm = system_manager_create();
    get_system_uptime(sm);
    get_system_time(sm);
    get_kernel_version(sm);
    get_running_services(sm);

    Logger* log = getLoggerInstance();
    log->log(LOG_INFO, "System uptime: %.0f seconds", sm->uptime_seconds);
    log->log(LOG_INFO, "System time  : %s", sm->sys_time);
    log->log(LOG_INFO, "Kernel       : %s", sm->kernel_version);

    system_manager_destroy(sm);
    return 0;
}

// static void system_printInfo(void) {
//     SystemManager* sm = system_manager_create();
//     get_system_uptime(sm);
//     get_system_time(sm);
//     get_kernel_version(sm);
//     get_running_services(sm);

//     Logger* log = getLoggerInstance();
//     log->log(LOG_INFO, "===== System Info =====");
//     log->log(LOG_INFO, "Uptime : %.0f sec", sm->uptime_seconds);
//     log->log(LOG_INFO, "Time   : %s", sm->sys_time);
//     log->log(LOG_INFO, "Kernel : %s", sm->kernel_version);
//     log->log(LOG_INFO, "Running Services:\n%s", sm->running_services);
//     log->log(LOG_INFO, "=======================");

//     system_manager_destroy(sm);
// }

Subsystem System = {
    .name = "System",
    .getStatus = system_getStatus,
    //.printInfo = system_printInfo
};
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subsystem.h"
#include "ram.h"
#include "logger.h"

static RamManager* g_ram_mgr = NULL;

RamManager* ram_manager_create(void) {
    if (g_ram_mgr != NULL) return g_ram_mgr;
    g_ram_mgr = calloc(1, sizeof(RamManager));
    return g_ram_mgr;
}

void ram_manager_destroy(void) {
    if (g_ram_mgr) {
        free(g_ram_mgr);
        g_ram_mgr = NULL;
    }
}

void get_ram_usage(RamManager* ram) {
    if (!ram) return;
    FILE* fp = fopen("/proc/meminfo", "r");
    if (!fp) return;

    char key[64];
    unsigned long value;
    char unit[32];

    while (fscanf(fp, "%63s %lu %31s\n", key, &value, unit) == 3) {
        if (strcmp(key, "MemTotal:") == 0) {
            ram->total_ram_kb = value;
        } else if (strcmp(key, "MemAvailable:") == 0) {
            ram->free_ram_kb = value;
        }
    }
    fclose(fp);
    ram->used_ram_kb = ram->total_ram_kb - ram->free_ram_kb;
}

void get_swap_usage(RamManager* ram) {
    if (!ram) return;
    FILE* fp = fopen("/proc/meminfo", "r");
    if (!fp) return;

    char key[64];
    unsigned long value;
    char unit[32];

    while (fscanf(fp, "%63s %lu %31s\n", key, &value, unit) == 3) {
        if (strcmp(key, "SwapTotal:") == 0) {
            ram->total_swap_kb = value;
        } else if (strcmp(key, "SwapFree:") == 0) {
            ram->free_swap_kb = value;
        }
    }
    fclose(fp);
    ram->used_swap_kb = ram->total_swap_kb - ram->free_swap_kb;
}

void get_top_process_ram(RamManager* ram) {
    if (!ram) return;
    FILE* pipe = popen("ps -eo comm,%mem --sort=-%mem --no-headers | head -5", "r");
    if (!pipe) return;

    ram->top_processes[0] = '\0'; // reset buffer
    char line[128];
    while (fgets(line, sizeof(line), pipe)) {
        strcat(ram->top_processes, line);
    }
    pclose(pipe);
}

static void ram_printInfo(void) {
    RamManager* ram = ram_manager_create();
    get_ram_usage(ram);
    get_swap_usage(ram);
    get_top_process_ram(ram);

    Logger* log = getLoggerInstance();

    log->log(LOG_INFO, "===== RAM Information =====");
    log->log(LOG_INFO, "RAM Total : %lu MB", ram->total_ram_kb / 1024);
    log->log(LOG_INFO, "RAM Used  : %lu MB", ram->used_ram_kb / 1024);
    log->log(LOG_INFO, "RAM Free  : %lu MB", ram->free_ram_kb / 1024);

    log->log(LOG_INFO, "Swap Total: %lu MB", ram->total_swap_kb / 1024);
    log->log(LOG_INFO, "Swap Used : %lu MB", ram->used_swap_kb / 1024);
    log->log(LOG_INFO, "Swap Free : %lu MB", ram->free_swap_kb / 1024);

    log->log(LOG_INFO, "Top 5 RAM-consuming processes:");
    log->log(LOG_INFO, "\n%s", ram->top_processes);

    log->log(LOG_INFO, "=============================\n");
}


static int ram_getStatus(void) {
    RamManager* ram = ram_manager_create();
    get_ram_usage(ram);

    double usage_percent = (ram->used_ram_kb * 100.0) / ram->total_ram_kb;

    Logger* log = getLoggerInstance();
    log->log(LOG_INFO, "RAM usage = %.2f%%", usage_percent);

    return (usage_percent > 80.0) ? 1 : 0;
}

Subsystem RAM = {
    .name = "RAM",
    .getStatus = ram_getStatus,
   // .printInfo = ram_printInfo
};


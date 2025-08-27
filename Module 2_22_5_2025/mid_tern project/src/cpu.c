#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <logger.h>
static void update_core_count(CpuManager *self) {
    self->core_count = (int)sysconf(_SC_NPROCESSORS_ONLN);
}

static void update_cpu_times(CpuManager *self) {
    FILE *f = fopen("/proc/stat", "r");
    if (!f) return;

    char line[256];
    int core = -1;

    int idx = 0;
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "cpu", 3) == 0) {
            if (line[3] == ' ') {
                core = -1; // tổng
                idx = 0;
            } else {
                core = atoi(line + 3);
                idx = core + 1;
            }

            unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
            sscanf(line + (core == -1 ? 4 : 5),
                   "%llu %llu %llu %llu %llu %llu %llu %llu",
                   &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal);

            unsigned long long total = user + nice + system + idle + iowait + irq + softirq + steal;

            self->idle_cur[idx]  = idle + iowait;
            self->total_cur[idx] = total;
        } else break;
    }
    fclose(f);
}

static void calculate_idle_total(CpuManager *self) {
    for (int i = 0; i <= self->core_count; i++) {
        unsigned long long prev_idle = self->idle_prev[i];
        unsigned long long prev_total = self->total_prev[i];
        unsigned long long cur_idle = self->idle_cur[i];
        unsigned long long cur_total = self->total_cur[i];

        unsigned long long delta_total = cur_total - prev_total;
        unsigned long long delta_idle = cur_idle - prev_idle;

        double usage = (delta_total > 0) ?
            (100.0 * (delta_total - delta_idle) / delta_total) : 0.0;

        if (i == 0) {
            self->total_usage = usage;
        } else {
            self->usage_percent[i-1] = usage;
        }

        // update prev
        self->idle_prev[i]  = cur_idle;
        self->total_prev[i] = cur_total;
    }
}

void cpu_update_usage(CpuManager *self) {
    update_cpu_times(self);
    calculate_idle_total(self);
}

void cpu_update_temperature(CpuManager *self) {
    FILE *f = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if (!f) {
        self->temperature_celsius = -1.0;
        return;
    }
    int temp_milli;
    if (fscanf(f, "%d", &temp_milli) == 1) {
        self->temperature_celsius = temp_milli / 1000.0;
    }
    fclose(f);
}

void cpu_update_frequency(CpuManager *self) {
    FILE *f = fopen("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq", "r");
    if (!f) {
        self->frequency_mhz = -1.0;
        return;
    }
    int freq_khz;
    if (fscanf(f, "%d", &freq_khz) == 1) {
        self->frequency_mhz = freq_khz / 1000.0;
    }
    fclose(f);
}

void cpu_update_top_process(CpuManager *self) {
    FILE *fp = popen("ps -eo comm,%cpu --sort=-%cpu | head -n 6", "r");
    if (!fp) return;

    char line[128];
    fgets(line, sizeof(line), fp); // skip header

    int idx = 0;
    while (fgets(line, sizeof(line), fp) && idx < 5) {
        sscanf(line, "%63s", self->top_processes[idx]);
        idx++;
    }
    self->top_process_count = idx;
    pclose(fp);
}

/* ==== Getter ==== */
double cpu_get_total_usage_percent(CpuManager *mgr) { return mgr->total_usage; }
double cpu_get_core_usage_percent(CpuManager *mgr, int core) {
    if (core < 0 || core >= mgr->core_count) return -1.0;
    return mgr->usage_percent[core];
}
double cpu_get_frequency_mhz(CpuManager *mgr) { return mgr->frequency_mhz; }
double cpu_get_temperature_celsius(CpuManager *mgr) { return mgr->temperature_celsius; }

/* ==== Create / Destroy ==== */
CpuManager *cpu_manager_create(void) {
    CpuManager *mgr = calloc(1, sizeof(CpuManager));
    if (!mgr) return NULL;

    update_core_count(mgr);
    int n = mgr->core_count;

    mgr->usage_percent = calloc(n, sizeof(double));
    mgr->idle_prev  = calloc(n+1, sizeof(unsigned long long));
    mgr->total_prev = calloc(n+1, sizeof(unsigned long long));
    mgr->idle_cur   = calloc(n+1, sizeof(unsigned long long));
    mgr->total_cur  = calloc(n+1, sizeof(unsigned long long));

    // init prev = cur
    update_cpu_times(mgr);
    for (int i = 0; i <= n; i++) {
        mgr->idle_prev[i]  = mgr->idle_cur[i];
        mgr->total_prev[i] = mgr->total_cur[i];
    }

    return mgr;
}

void cpu_manager_destroy(CpuManager *mgr) {
    if (!mgr) return;
    free(mgr->usage_percent);
    free(mgr->idle_prev);
    free(mgr->total_prev);
    free(mgr->idle_cur);
    free(mgr->total_cur);
    free(mgr);
}

/* ==== Subsystem binding ==== */
static int cpu_get_status(void) {
    CpuManager* mgr = cpu_manager_create();
    cpu_update_usage(mgr);
    cpu_update_top_process(mgr);   // <-- bổ sung

    Logger* log = getLoggerInstance();
    for (int i = 0; i < mgr->top_process_count; i++) {
        log->log(LOG_INFO, "CPU Top %d: %s", i+1, mgr->top_processes[i]);
    }

    int status = (int)cpu_get_total_usage_percent(mgr);
    cpu_manager_destroy(mgr);
    return status;
}


Subsystem CPU = {
    .name = "CPU",
    .getStatus = cpu_get_status
};

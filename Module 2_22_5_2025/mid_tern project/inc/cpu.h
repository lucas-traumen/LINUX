#ifndef CPU_H_
#define CPU_H_

#include <stdint.h>
#include "subsystem.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CpuManager CpuManager;

CpuManager *cpu_manager_create(void);
void cpu_manager_destroy(CpuManager *mgr);

void cpu_update_usage(CpuManager *mgr);
void cpu_update_temperature(CpuManager *mgr);
void cpu_update_frequency(CpuManager *mgr);
void cpu_update_top_process(CpuManager *mgr);

// Getter public 
double cpu_get_total_usage_percent(CpuManager *mgr); 
double cpu_get_core_usage_percent(CpuManager *mgr, int core);
double cpu_get_frequency_mhz(CpuManager *mgr);
double cpu_get_temperature_celsius(CpuManager *mgr);

// Subsystem toàn cục
extern Subsystem CPU;

struct CpuManager {
    int core_count;
    double total_usage;          // % tổng
    double *usage_percent;       // % từng core
    double frequency_mhz;        // MHz
    double temperature_celsius;  // °C

    // lưu idle/total để tính delta
    unsigned long long *idle_prev;
    unsigned long long *total_prev;
    unsigned long long *idle_cur;
    unsigned long long *total_cur;

    // top process
    char top_processes[5][64];
    int top_process_count;
};

#ifdef __cplusplus
}
#endif

#endif // CPU_H_

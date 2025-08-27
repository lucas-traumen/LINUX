#ifndef RAM_H
#define RAM_H

#include "factory.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    unsigned long total_ram_kb;
    unsigned long free_ram_kb;
    unsigned long used_ram_kb;

    unsigned long total_swap_kb;
    unsigned long free_swap_kb;
    unsigned long used_swap_kb;

    char top_processes[1024]; // lưu danh sách top 5 process theo RAM
} RamManager;

RamManager* ram_manager_create(void);
void ram_manager_destroy(void);

void get_ram_usage(RamManager* ram);
void get_swap_usage(RamManager* ram);
void get_top_process_ram(RamManager* ram);

#ifdef __cplusplus
}
#endif

#endif

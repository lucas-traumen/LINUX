#ifndef ROM_H
#define ROM_H


#include "subsystem.h"
#include "factory.h"
#include "logger.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    unsigned long total_space_kb;
    unsigned long used_space_kb;
    unsigned long free_space_kb;

    double read_speed_kbps;
    double write_speed_kbps;

    unsigned long long read_ops;
    unsigned long long write_ops;
    unsigned long long read_iops;
    unsigned long long write_iops;

    char partitions[2048];   // lưu danh sách phân vùng và dung lượng
} StorageManager;

StorageManager* storage_manager_create(void);
void storage_manager_destroy(StorageManager* sm);

void get_disk_usage(StorageManager* sm);
void get_io_stats(StorageManager* sm);
void get_rw_speed(StorageManager* sm);

#ifdef __cplusplus
}
#endif

#endif 


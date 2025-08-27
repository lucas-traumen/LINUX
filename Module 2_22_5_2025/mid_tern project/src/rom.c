#include <string.h>
#include <unistd.h>
#include <sys/statvfs.h>
#include <stdio.h>
#include <stdlib.h>
#include "rom.h"

StorageManager* storage_manager_create(void) {
    StorageManager* sm = (StorageManager*)malloc(sizeof(StorageManager));
    if (!sm) return NULL;
    memset(sm, 0, sizeof(StorageManager));
    return sm;
}

void storage_manager_destroy(StorageManager* sm) {
    if (sm) free(sm);
}

/* Lấy dung lượng ổ đĩa (phân vùng gốc /) */
void get_disk_usage(StorageManager* sm) {
    struct statvfs stat;
    if (statvfs("/", &stat) == 0) {
        sm->total_space_kb = (stat.f_blocks * stat.f_frsize) / 1024;
        sm->free_space_kb  = (stat.f_bfree  * stat.f_frsize) / 1024;
        sm->used_space_kb  = sm->total_space_kb - sm->free_space_kb;

        snprintf(sm->partitions, sizeof(sm->partitions),
                 "/ partition: Total=%lu MB, Used=%lu MB, Free=%lu MB\n",
                 sm->total_space_kb/1024,
                 sm->used_space_kb/1024,
                 sm->free_space_kb/1024);
    }
}

/* Lấy số lượng I/O từ /proc/diskstats */
void get_io_stats(StorageManager* sm) {
    FILE* f = fopen("/proc/diskstats", "r");
    if (!f) return;

    char dev[32];
    unsigned long rd_ios, rd_merges, rd_sectors, rd_ticks;
    unsigned long wr_ios, wr_merges, wr_sectors, wr_ticks;
    unsigned long ios_pgr, tot_ticks, rq_ticks;

    while (fscanf(f, " %*d %*d %31s %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu",
                  dev,
                  &rd_ios, &rd_merges, &rd_sectors, &rd_ticks,
                  &wr_ios, &wr_merges, &wr_sectors, &wr_ticks,
                  &ios_pgr, &tot_ticks, &rq_ticks) == 12)
    {
        if (strncmp(dev, "sda", 3) == 0 || strncmp(dev, "nvme0n1", 7) == 0) {
            sm->read_ops  = rd_ios;
            sm->write_ops = wr_ios;
            sm->read_iops = rd_sectors;   // đơn giản: số sector
            sm->write_iops = wr_sectors;
            break;
        }
    }
    fclose(f);
}

/* Giả lập tốc độ đọc/ghi (ở mức demo). 
   Thực tế: phải đo chênh lệch rd_sectors/wr_sectors theo thời gian */
void get_rw_speed(StorageManager* sm) {
    sm->read_speed_kbps = sm->read_iops / 2.0;   // demo: scale từ IOPS
    sm->write_speed_kbps = sm->write_iops / 2.0;
}
static int storage_getStatus(void) {
    StorageManager* sm = storage_manager_create();
    get_disk_usage(sm);
    get_io_stats(sm);
    get_rw_speed(sm);

    double used_percent = (sm->used_space_kb * 100.0) / sm->total_space_kb;

    Logger* log = getLoggerInstance();
    log->log(LOG_INFO, "Disk usage: %.2f%%", used_percent);
    log->log(LOG_INFO, "R=%.2f KB/s, W=%.2f KB/s, IOPS R=%llu W=%llu",
             sm->read_speed_kbps, sm->write_speed_kbps,
             sm->read_iops, sm->write_iops);

    storage_manager_destroy(sm);
    return (used_percent > 90.0) ? 1 : 0;
}

// static void storage_printInfo(void) {
//     StorageManager* sm = storage_manager_create();
//     get_disk_usage(sm);
//     get_io_stats(sm);
//     get_rw_speed(sm);

//     Logger* log = getLoggerInstance();
//     log->log(LOG_INFO, "===== Storage Info =====");
//     log->log(LOG_INFO, "%s", sm->partitions);
//     log->log(LOG_INFO, "Read Speed : %.2f KB/s", sm->read_speed_kbps);
//     log->log(LOG_INFO, "Write Speed: %.2f KB/s", sm->write_speed_kbps);
//     log->log(LOG_INFO, "Read Ops   : %llu", sm->read_ops);
//     log->log(LOG_INFO, "Write Ops  : %llu", sm->write_ops);
//     log->log(LOG_INFO, "========================");

//     storage_manager_destroy(sm);
// }

Subsystem ROM = {
    .name = "ROM",
    .getStatus = storage_getStatus,
  //  .printInfo = storage_printInfo
};
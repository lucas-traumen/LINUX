#include "network.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <factory.h>
/* get time in ms */
static unsigned long long now_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000ULL + ts.tv_nsec / 1000000ULL;
}

/* đọc từ /proc/net/dev */
void network_update_status(NetworkManager* self) {
    FILE *f = fopen("/proc/net/dev", "r");
    if (!f) return;

    char line[256];
    unsigned long long rx_bytes=0, tx_bytes=0;
    unsigned long long rx_packets=0, tx_packets=0;

    fgets(line, sizeof(line), f); // skip header
    fgets(line, sizeof(line), f);

    while (fgets(line, sizeof(line), f)) {
        char iface[32];
        unsigned long long rbytes, rpack, rerrs, rdrop, rfifo, rframe, rcomp, rmulti;
        unsigned long long tbytes, tpack, terrs, tdrop, tfifo, tcolls, tcarrier, tcomp;

        sscanf(line, "%31[^:]: %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
               iface,
               &rbytes, &rpack, &rerrs, &rdrop, &rfifo, &rframe, &rcomp, &rmulti,
               &tbytes, &tpack, &terrs, &tdrop, &tfifo, &tcolls, &tcarrier, &tcomp);

        rx_bytes   += rbytes;
        tx_bytes   += tbytes;
        rx_packets += rpack;
        tx_packets += tpack;
    }
    fclose(f);

    unsigned long long cur_time = now_ms();
    unsigned long long delta_time = cur_time - self->prev_time_ms;
    if (delta_time > 0) {
        unsigned long long delta_rx = rx_bytes - self->prev_rx_bytes;
        unsigned long long delta_tx = tx_bytes - self->prev_tx_bytes;

        self->download_speed_kbps = (delta_rx * 1000.0 / delta_time) / 1024.0;
        self->upload_speed_kbps   = (delta_tx * 1000.0 / delta_time) / 1024.0;
    }

    self->total_rx_bytes = rx_bytes;
    self->total_tx_bytes = tx_bytes;
    self->total_rx_packets = rx_packets;
    self->total_tx_packets = tx_packets;

    self->prev_rx_bytes = rx_bytes;
    self->prev_tx_bytes = tx_bytes;
    self->prev_time_ms = cur_time;
}

/* đọc số lượng kết nối từ /proc/net/tcp */
void network_update_connections(NetworkManager* self) {
    FILE *f = fopen("/proc/net/tcp", "r");
    if (!f) return;

    char line[256];
    fgets(line, sizeof(line), f); // skip header

    int count = 0;
    while (fgets(line, sizeof(line), f)) count++;
    fclose(f);

    self->connection_count = count;
}

/* đọc ip address từ "ip -o -4 addr show" */
void network_update_ip(NetworkManager* self) {
    FILE *fp = popen("ip -o -4 addr show | awk '{print $4}'", "r");
    if (!fp) return;

    char line[64];
    int idx = 0;
    while (fgets(line, sizeof(line), fp) && idx < 8) {
        line[strcspn(line, "\n")] = 0;
        strncpy(self->ip_addresses[idx], line, sizeof(self->ip_addresses[idx]));
        idx++;
    }
    self->ip_count = idx;
    pclose(fp);
}

/* getter */
double network_get_upload(NetworkManager* mgr) { return mgr->upload_speed_kbps; }
double network_get_download(NetworkManager* mgr) { return mgr->download_speed_kbps; }
int    network_get_connection_count(NetworkManager* mgr) { return mgr->connection_count; }

/* create/destroy */
NetworkManager* network_manager_create(void) {
    NetworkManager* mgr = calloc(1, sizeof(NetworkManager));
    if (!mgr) return NULL;
    mgr->prev_time_ms = now_ms();
    network_update_status(mgr);
    return mgr;
}

void network_manager_destroy(NetworkManager* mgr) {
    if (mgr) free(mgr);
}

/* Subsystem binding */
static int network_get_status(void) {
    NetworkManager* mgr = network_manager_create();
    network_update_status(mgr);
    network_update_connections(mgr);
    network_update_ip(mgr);

    Logger* log = getLoggerInstance();
    log->log(LOG_INFO, "Net: Up %.2f KB/s, Down %.2f KB/s, Conn=%d",
             mgr->upload_speed_kbps, mgr->download_speed_kbps, mgr->connection_count);
    for (int i = 0; i < mgr->ip_count; i++) {
        log->log(LOG_INFO, "IP[%d] = %s", i, mgr->ip_addresses[i]);
    }
    log->log(LOG_INFO, "Packets: RX=%llu TX=%llu",
             mgr->total_rx_packets, mgr->total_tx_packets);

    network_manager_destroy(mgr);
    return 0;
}


Subsystem Network = {
    .name = "Network",
    .getStatus = network_get_status,
};

#ifndef NETWORK_H
#define NETWORK_H

#include "subsystem.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    double upload_speed_kbps;      // Tốc độ upload hiện tại
    double download_speed_kbps;    // Tốc độ download hiện tại

    unsigned long long total_tx_bytes;
    unsigned long long total_rx_bytes;

    unsigned long long total_tx_packets;
    unsigned long long total_rx_packets;

    int connection_count;          // số lượng kết nối TCP
    char ip_addresses[8][64];      // lưu tối đa 8 interface
    int ip_count;

    // prev snapshot
    unsigned long long prev_tx_bytes;
    unsigned long long prev_rx_bytes;

    unsigned long long prev_time_ms;

} NetworkManager;

/* ==== API ==== */
NetworkManager* network_manager_create(void);
void network_manager_destroy(NetworkManager* mgr);

void network_update_status(NetworkManager* mgr);
void network_update_connections(NetworkManager* mgr);
void network_update_ip(NetworkManager* mgr);

/* Getter */
double network_get_upload(NetworkManager* mgr);
double network_get_download(NetworkManager* mgr);
int    network_get_connection_count(NetworkManager* mgr);

extern Subsystem NETWORK;

#ifdef __cplusplus
}
#endif

#endif

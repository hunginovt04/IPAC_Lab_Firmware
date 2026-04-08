#ifndef BLE_HANDLE_H
#define BLE_HANDLE_H

#include "config.h"

/* BLE configuration */
#define BLE_EVT_QUEUE_LEN 256
#define BLE_PROC_TASK_STACK 4096
#define BLE_PRINT_TASK_STACK 4096
#define BLE_PROC_TASK_PRIO 6
#define BLE_PRINT_TASK_PRIO 5
#define BLE_PRINT_TASK_CORE 1
#define BLE_PROC_TASK_CORE 0

extern int rssi_1s_count;
extern esp_ble_scan_params_t ble_scan_params;

void ble_rssi_scan_callback(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);
void uart_init(void);
void ble_init(void);

#endif
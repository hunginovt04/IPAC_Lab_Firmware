#include "ble_handle.h"

// Dia chi Mac 4 beacon
static const uint8_t BLE_TARGET_BEACON[4][6] = {
    {0xC8, 0x2E, 0x18, 0x67, 0x7E, 0xDA},
    {0x80, 0xF3, 0xDA, 0xAD, 0x7A, 0x7E},
    {0x80, 0xF3, 0xDA, 0x62, 0x07, 0x16},
    {0x80, 0xF3, 0xDA, 0x62, 0xC9, 0x4A},
};

// Bien dem so luong RSSI Scan duoc
int rssi_1s_count = 0;

// Ham init uart
void uart_init(void)
{
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    uart_param_config(UART_PORT, &uart_config);

    uart_set_pin(UART_PORT, TXD_PIN, RXD_PIN,
                 UART_PIN_NO_CHANGE,
                 UART_PIN_NO_CHANGE);

    uart_driver_install(UART_PORT, 1024, 1024, 0, NULL, 0);
}

/* Tham so khoi tao (passive scan) */
esp_ble_scan_params_t ble_scan_params = {
    .scan_type = BLE_SCAN_TYPE_PASSIVE,
    .own_addr_type = BLE_ADDR_TYPE_PUBLIC,
    .scan_filter_policy = BLE_SCAN_FILTER_ALLOW_ALL,
    .scan_interval = 0x30,
    .scan_window = 0x30,
    .scan_duplicate = BLE_SCAN_DUPLICATE_DISABLE};

void ble_ibeacon_appRegister()
{
    esp_err_t status;

    ESP_LOGI("BLE SCAN", "register callback");

    // register the scan callback function to the gap module
    if ((status = esp_ble_gap_register_callback(ble_rssi_scan_callback)) != ESP_OK)
    {
        ESP_LOGE("BLE SCAN", "gap register error, error code = %x", status);
        return;
    }
}

// Ham init BLE
void ble_init(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        nvs_flash_erase();
        nvs_flash_init();
    }

    esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT);

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    esp_bt_controller_init(&bt_cfg);
    esp_bt_controller_enable(ESP_BT_MODE_BLE);

    esp_bluedroid_init();
    esp_bluedroid_enable();

    // Đăng ký callback
    ble_ibeacon_appRegister();

    esp_ble_gap_set_scan_params(&ble_scan_params);
}

void ble_rssi_scan_callback(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    switch (event)
    {

    case ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT:
    {
        ESP_LOGI("BLE", "start scanning...");
        esp_err_t err = esp_ble_gap_start_scanning(0);
        ESP_LOGI("BLE", "ret = %s", esp_err_to_name(err));
        break;
    }

    case ESP_GAP_BLE_SCAN_START_COMPLETE_EVT:
        ESP_LOGI("BLE", "status = %d", param->scan_start_cmpl.status);
        break;

    case ESP_GAP_BLE_SCAN_RESULT_EVT:
        esp_ble_gap_cb_param_t *scan_result = (esp_ble_gap_cb_param_t *)param;
        if (scan_result->scan_rst.search_evt == ESP_GAP_SEARCH_INQ_RES_EVT)
        {
            uint8_t *addr = scan_result->scan_rst.bda;
            int rssi = scan_result->scan_rst.rssi;
            for (int i = 0; i < NUM_BEACONS; i++)
            {
                if (memcmp(addr, BLE_TARGET_BEACON[i], 6) == 0)
                {
                    rssi_1s_count++;
                    char buffer[50];
                    sprintf(buffer, "%d %d\n", i + 1, rssi);
                    // printf(buffer);

                    // Gui uart
                    uart_write_bytes(UART_PORT, buffer, strlen(buffer));
                    printf("%d %d\n",i+1,rssi);
                }
            }
        }
        break;

    default:
        break;
    }
}

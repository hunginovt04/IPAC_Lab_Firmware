#include "config.h"
#include "ble_handle.h"

// Su dung FreeRtos in ra so luong RSSI scan duoc trong 1s
void print_task(void *arg)
{
    while (1)
    {
        printf("So luong RSSI trong 1s: %d\n", rssi_1s_count);
        rssi_1s_count = 0;
        // Doi 1s in mot lan
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main()
{
    ble_init();
    uart_init();

    // Khoi tao task
    xTaskCreatePinnedToCore(
        print_task,
        "print_task",
        4096,
        NULL,
        5,
        NULL,
        1);

    while (1)
    {
    }
}
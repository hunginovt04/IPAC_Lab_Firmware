#ifndef LCD_CONTROL_H
#define LCD_CONTROL_H

#include "config.h"

void lcd_display_training_mode(Adafruit_ILI9341 &tft,
     RSSI_Data *wifi_rssi_data, RSSI_Data *ble_rssi_data, IMU_Data &imu_data);
void lcd_display_reality_mode(Adafruit_ILI9341 &tft, IMU_Data &imu_data, int valve_status, int extinguish_mode);
#endif // LCD_CONTROL_H
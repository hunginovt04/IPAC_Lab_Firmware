#include "ui/lcd_control.h"

extern bool map_updated;
extern bool user_updated;
extern bool fire_updated;

extern Map_data map_data;
extern float north_offset;
extern int fire_map[MAP_WIDTH_MAX][MAP_HEIGHT_MAX];
extern User_data user_data;

void evaluate_rssi_value(Adafruit_ILI9341 &tft, int rssi_value, int x, int y)
{
    if (rssi_value == -100)
    {
        tft.setCursor(x, y);
        tft.setTextColor(RED);
        tft.println("Lost signal");
        tft.setTextColor(WHITE);
    }
    else if (rssi_value > -100 && rssi_value < -80)
    {
        tft.setCursor(x, y);
        tft.setTextColor(ORANGE);
        tft.println("Weak");
        tft.setTextColor(WHITE);
    }
    else if (rssi_value >= -80 && rssi_value <= -30)
    {
        tft.setCursor(x, y);
        tft.setTextColor(YELLOW);
        tft.println("Normal");
        tft.setTextColor(WHITE);
    }
    else if (rssi_value > -30 && rssi_value < 0)
    {
        tft.setCursor(x, y);
        tft.setTextColor(GREEN);
        tft.println("Strong");
        tft.setTextColor(WHITE);
    }
    else
    {
        tft.setCursor(x, y);
        tft.setTextColor(RED);
        tft.println("Not Valid");
        tft.setTextColor(WHITE);
    }
}
void lcd_display_training_mode(Adafruit_ILI9341 &tft,
                               RSSI_Data *wifi_rssi_data, RSSI_Data *ble_rssi_data, IMU_Data &imu_data)
{
    // RSSI data
    // Clear previous data
    tft.fillRect(70, 50, 14, 40, BLACK);
    tft.fillRect(140, 50, 200, 40, BLACK);

    tft.setTextColor(WHITE);
    tft.setCursor(70, 50);
    tft.println(String(wifi_rssi_data[0].ssid_id));
    tft.setCursor(140, 50);
    tft.println(String(wifi_rssi_data[0].rssi));
    evaluate_rssi_value(tft, wifi_rssi_data[0].rssi, 200, 50);

    tft.setCursor(70, 60);
    tft.println(String(wifi_rssi_data[1].ssid_id));
    tft.setCursor(140, 60);
    tft.println(String(wifi_rssi_data[1].rssi));
    evaluate_rssi_value(tft, wifi_rssi_data[1].rssi, 200, 60);

    tft.setCursor(70, 70);
    tft.println(String(wifi_rssi_data[2].ssid_id));
    tft.setCursor(140, 70);
    tft.println(String(wifi_rssi_data[2].rssi));
    evaluate_rssi_value(tft, wifi_rssi_data[2].rssi, 200, 70);

    tft.setCursor(70, 80);
    tft.println(String(wifi_rssi_data[3].ssid_id));
    tft.setCursor(140, 80);
    tft.println(String(wifi_rssi_data[3].rssi));
    evaluate_rssi_value(tft, wifi_rssi_data[3].rssi, 200, 80);

    // BLE RSSI data
    tft.fillRect(70, 115, 14, 40, BLACK);
    tft.fillRect(140, 115, 200, 40, BLACK);

    tft.setTextColor(WHITE);
    tft.setCursor(70, 115);
    tft.println(String(ble_rssi_data[0].ssid_id));
    tft.setCursor(140, 115);
    tft.println(String(ble_rssi_data[0].rssi));
    evaluate_rssi_value(tft, ble_rssi_data[0].rssi, 200, 115);

    tft.setCursor(70, 125);
    tft.println(String(ble_rssi_data[1].ssid_id));
    tft.setCursor(140, 125);
    tft.println(String(ble_rssi_data[1].rssi));
    evaluate_rssi_value(tft, ble_rssi_data[1].rssi, 200, 125);

    tft.setCursor(70, 135);
    tft.println(String(ble_rssi_data[2].ssid_id));
    tft.setCursor(140, 135);
    tft.println(String(ble_rssi_data[2].rssi));
    evaluate_rssi_value(tft, ble_rssi_data[2].rssi, 200, 135);

    tft.setCursor(70, 145);
    tft.println(String(ble_rssi_data[3].ssid_id));
    tft.setCursor(140, 145);
    tft.println(String(ble_rssi_data[3].rssi));
    evaluate_rssi_value(tft, ble_rssi_data[3].rssi, 200, 145);

    // IMU data
    // Clear previous data
    tft.fillRect(120, 180, 39, 40, BLACK);
    tft.fillRect(195, 180, 39, 40, BLACK);
    tft.fillRect(270, 180, 39, 40, BLACK);

    tft.setCursor(120, 180);
    tft.println(String(imu_data.acc.x));
    tft.setCursor(195, 180);
    tft.println(String(imu_data.acc.y));
    tft.setCursor(270, 180);
    tft.println(String(imu_data.acc.z));

    tft.setCursor(120, 190);
    tft.println(String(imu_data.mag.x));
    tft.setCursor(195, 190);
    tft.println(String(imu_data.mag.y));
    tft.setCursor(270, 190);
    tft.println(String(imu_data.mag.z));

    tft.setCursor(120, 200);
    tft.println(String(imu_data.gyro.x));
    tft.setCursor(195, 200);
    tft.println(String(imu_data.gyro.y));
    tft.setCursor(270, 200);
    tft.println(String(imu_data.gyro.z));

    tft.setCursor(120, 210);
    tft.println(String(imu_data.euler.x));
    tft.setCursor(195, 210);
    tft.println(String(imu_data.euler.y));
    tft.setCursor(270, 210);
    tft.println(String(imu_data.euler.z));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void coordinate_to_pixel(float coor_x, float coor_y, int &pixel_x, int &pixel_y)
{
    if (coor_x < 0)
        coor_x = 0;
    if (coor_x > 10)
        coor_x = 10;
    if (coor_y < 0)
        coor_y = 0;
    if (coor_y > 10)
        coor_y = 10;
    // X: 0-10 to pixel 10-210 (200 pixels for 10 units)
    pixel_x = round(10 + (coor_x / 10.0f) * 200);
    // Y: 0-10 to pixel 230-30 (200 pixels for 10 units)
    pixel_y = round(230 - (coor_y / 10.0f) * 200);
}

void lcd_display_reality_mode(Adafruit_ILI9341 &tft, IMU_Data &imu_data, int valve_status, int extinguish_mode)
{
    if (map_updated)
    {
        map_updated = false;
        for (int i = 0; i < map_data.width; i++)
        {
            for (int j = 0; j < map_data.height; j++)
            {
                int pixel_x, pixel_y;
                coordinate_to_pixel(i, j, pixel_x, pixel_y);
                if (map_data.map_cells[i][j] == 1)
                {
                    tft.drawRect(pixel_x, pixel_y - 20, 20, 20, WHITE);
                }
                else
                {
                    tft.drawRect(pixel_x, pixel_y - 20, 20, 20, WHITE);
                    tft.drawLine(pixel_x, pixel_y - 20, pixel_x + 20, pixel_y, RED);
                    for (int i = 1; i < 4; i ++)
                    {
                        tft.drawLine(
                            pixel_x,
                            pixel_y - i*5,
                            pixel_x + i*5,
                            pixel_y,
                            RED);
                        tft.drawLine(
                            pixel_x + i*5,
                            pixel_y - 20,
                            pixel_x + 20,
                            pixel_y - i*5,
                            RED);
                    }
                }
            }
        }
    }
    if (fire_updated)
    {
        fire_updated = false;
    }
    if (user_updated)
    {
        user_updated = false;
    }
}
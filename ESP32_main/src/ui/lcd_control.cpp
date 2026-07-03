#include "ui/lcd_control.h"

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
    // Normalize outlier
    if (coor_x < 0) coor_x = 0;
    if (coor_x > 10) coor_x = 10;
    if (coor_y < 0) coor_y = 0;
    if (coor_y > 10) coor_y = 10;

    // X: Mapping from 0–10 (descartes) to 9–211 (pixel)
    pixel_x = round(9 + (coor_x / 10.0f) * (211 - 9));
    // Y: Mapping from 0–10 (descartes) to 221–19 (pixel) (reverse y axis with ILI9341)
    pixel_y = round(221 - (coor_y / 10.0f) * (221 - 19));
}

void lcd_setup_map_outline(Adafruit_ILI9341 &tft)
{
    tft.setTextColor(STATIC_TEXT_COLOR);
    tft.setTextSize(1);
    
    // Vẽ các trục của map
    tft.drawFastVLine(9, 19, 202, MAP_GRID_COLOR);
    tft.drawFastHLine(9, 221, 202, MAP_GRID_COLOR);
    tft.drawFastVLine(217, 0, 240, MAP_GRID_COLOR);

    // Trục Y - Hướng north của map
    tft.setCursor(0, 16);
    tft.println("10");
    tft.setCursor(1, 36);
    tft.println("9");
    tft.setCursor(1, 56);
    tft.println("8");
    tft.setCursor(1, 76);
    tft.println("7");
    tft.setCursor(1, 96);
    tft.println("6");
    tft.setCursor(1, 116);
    tft.println("5");
    tft.setCursor(1, 136);
    tft.println("4");
    tft.setCursor(1, 156);
    tft.println("3");
    tft.setCursor(1, 176);
    tft.println("2");
    tft.setCursor(1, 196);
    tft.println("1");

    // Trục x
    tft.setCursor(27, 226);
    tft.println("1");
    tft.setCursor(47, 226);
    tft.println("2");
    tft.setCursor(67, 226);
    tft.println("3");
    tft.setCursor(87, 226);
    tft.println("4");
    tft.setCursor(107, 226);
    tft.println("5");
    tft.setCursor(127, 226);
    tft.println("6");
    tft.setCursor(147, 226);
    tft.println("7");
    tft.setCursor(167, 226);
    tft.println("8");
    tft.setCursor(187, 226);
    tft.println("9");
    tft.setCursor(207, 226);
    tft.println("10");
    tft.setCursor(1, 226);
    tft.println("0");
}

void lcd_display_map(Adafruit_ILI9341 &tft, Map_data &map_data)
{
    // Clear previous map
    tft.fillRect(10, 21, 200, 200, BACKGROUND_COLOR);

    // Draw new map
    for (int x = 0; x < map_data.width; x++)
    {
        for (int y = 0; y < map_data.height; y++)
        {
            if (map_data.map_cells[x][y] == 1)
            {
                int pixel_x, pixel_y;
                coordinate_to_pixel(x, y, pixel_x, pixel_y);
                tft.drawRect(pixel_x, pixel_y - 20, 20, 20, MAP_GRID_COLOR);
            }
        }
    }
}
void lcd_display_fire(Adafruit_ILI9341 &tft, Fire_data &fire_data)
{
    // Draw new fire
    for (int x = 0; x < MAP_WIDTH_MAX; x++)
    {
        for (int y = 0; y < MAP_HEIGHT_MAX; y++)
        {
            if (fire_data.fire_map[x][y] == 0) // Delete fire
            {
                int pixel_x, pixel_y;
                coordinate_to_pixel(x, y, pixel_x, pixel_y);
                tft.fillRect(pixel_x + 1, pixel_y - 19, 18, 18, BACKGROUND_COLOR);
            }else{

                int pixel_x, pixel_y;
                coordinate_to_pixel(x, y, pixel_x, pixel_y);
                tft.fillRect(pixel_x + 2, pixel_y - 18, 16, 16, fire_color[fire_data.fire_map[x][y]]);
            }
        }
    }
}
void lcd_display_user(Adafruit_ILI9341 &tft, User_data &user_data)
{
    // Clear previous user
    int last_pixel_x, last_pixel_y;
    coordinate_to_pixel(user_data.last_user_x, user_data.last_user_y, last_pixel_x, last_pixel_y);
    tft.fillCircle(last_pixel_x + 10, last_pixel_y - 10, 5, BACKGROUND_COLOR);

    // Draw new user
    int pixel_x, pixel_y;
    coordinate_to_pixel(user_data.user_x, user_data.user_y, pixel_x, pixel_y);
    tft.fillCircle(pixel_x + 10, pixel_y - 10, 5, USER_DOT_COLOR);
}


void lcd_display_reality_mode(Adafruit_ILI9341 &tft, IMU_Data &imu_data, Map_data &map_data, User_data &user_data,
                             Fire_data &fire_data, Valve_Data &valve_data)
{
    lcd_setup_map_outline(tft);
    if (map_updated)
    {
        map_updated = false;
        lcd_display_map(tft, map_data);
    }
    if (fire_updated)
    {
        fire_updated = false;
        lcd_display_fire(tft, fire_data);
    }
    if (user_updated)
    {
        user_updated = false;
        lcd_display_user(tft, user_data);
    }
}
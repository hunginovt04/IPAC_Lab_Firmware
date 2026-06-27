#include "apps/app_mode.h"

int last_data_sent[8] = {-100, -100, -100, -100, -100, -100, -100, -100}; // Initialize with default RSSI values

// Dữ liệu liên quan tới người dùng
//User_data user_data;
//User_data last_user_data;

// extern UserDisplay user;
// extern FlamesDisplay flames;
// extern MapDisplay exercise_map;

String training_topic = MQTT_TRAINING_TOPIC;//+ String(DEVICE_ID);
String real_topic = MQTT_REALITY_TOPIC;//+ String(DEVICE_ID);
String device_infor_topic = MQTT_DEVICE_INFOR_TOPIC; 
int device_id = DEVICE_ID;

// Get mode of system based on button states
void get_mode(ModeSystem &mode_of_system)
{
    if (is_sw2_on())
    {
        mode_of_system = is_sw1_on() ? TRAINING_MODE : DEFAULT_MODE;
    }
    else
    {
        mode_of_system = is_sw1_on() ? REALITY_MODE : DEFAULT_MODE;
    }
}

bool change_mode = false;
void mode_update(ModeSystem &mode_of_system)
{
    ModeSystem new_mode;
    get_mode(new_mode);
    if (new_mode != mode_of_system)
    {
        mode_of_system = new_mode;
        change_mode = true;
    }
}

void run_default_mode(Adafruit_ILI9341 &tft, RSSI_Data *wifi_rssi_data,
                      RSSI_Data *ble_rssi_data, String &message)
{
    if (change_mode)
    {
        change_mode = false;
        lcd_setup_outline(tft);
    }
    get_infor_msg(training_topic, real_topic, device_id, message);

    if (is_ready_to_publish())
    {
        publish_message(device_infor_topic, message);
    }
    lcd_default_mode_outline(tft, wifi_rssi_data, ble_rssi_data);
}

unsigned long last_display_time = 0;
void run_training_mode(Adafruit_ILI9341 &tft, RSSI_Data *wifi_rssi_data,
                       RSSI_Data *ble_rssi_data, IMU_Data &imu_data, String &message)
{
    if (change_mode)
    {
        change_mode = false;
        lcd_training_mode_outline(tft);
    }
    get_training_msg(wifi_rssi_data, ble_rssi_data, imu_data, message);
    
    if (is_ready_to_publish())
    {
        publish_message(training_topic, message);
        // for (int i = 0; i < 4; i++)
        // {
        //     last_data_sent[i] = wifi_rssi_data[i].rssi; // Reset the last sent data
        // }
        // for (int i = 4; i < 8; i++)
        // {
        //     last_data_sent[i] = ble_rssi_data[i - 4].rssi; // Reset the last sent data
        // }
    }
    if(millis() - last_display_time >= 100) // Update display every 1 second
    {
        last_display_time = millis();
        lcd_display_training_mode(tft, wifi_rssi_data, ble_rssi_data, imu_data);
    }
}
void run_reality_mode(Adafruit_ILI9341 &tft, RSSI_Data *wifi_rssi_data,
                      RSSI_Data *ble_rssi_data, IMU_Data &imu_data, String &message)
{
    Valve_Data valve_data;
    valve_data.valve_open_status = 0;
    valve_data.mode_status = 0;
    read_valve_open_status(&valve_data.valve_open_status, &valve_data.mode_status);
    
    if (change_mode)
    {
        change_mode = false;
        tft.fillScreen(BLACK);
        // lcd_setup_outline(tft);
        // lcd_reality_mode_outline(tft);
    }   
    get_real_msg(wifi_rssi_data, ble_rssi_data, imu_data, valve_data.valve_open_status, valve_data.mode_status, message);

    if (is_ready_to_publish())
    {
        publish_message(real_topic, message);
    }
    //tft_main_loop_handler(tft, user, flames, exercise_map, imu_data, valve_data);
    //lcd_display_reality_mode(tft, imu_data, valve_open_status, mode_status);
    tft_main_loop_handler(tft, user, flames, exercise_map, imu_data, valve_data);
    // // Xóa hiển thị người dùng và ngọn lửa
    // if (fire_updated)
    // {
    //     fire_display_delete(tft, last_fire);
    //     fire_updated = false;
    // }

    // if (user_updated)
    // {
    //     user_display_delete(tft, last_user_data);
    //     user_updated = false;
    // }

    // else
    // {
    //     user_display_delete(tft, user_data);
    // }

    // Check map_updated, vẽ lại layout map
    // if (map_updated)
    // {
    //     draw_reality_map(tft, last_map_grid, BLACK);
    //     draw_reality_not_map(tft, last_not_map_grid, BLACK);
    //     draw_reality_map(tft, map_grid, WHITE);
    //     draw_reality_not_map(tft, not_map_grid, BLUE);
    //     lcd_setup_reality_map_outline(tft);
    //     map_updated = false;
    // }
    // else
    // {
    //     draw_reality_map(tft, map_grid, WHITE);
    //     draw_reality_not_map(tft, not_map_grid, BLUE);
    //     lcd_setup_reality_map_outline(tft);
    // }
    // // Hiện thị ngọn lửa
    // fire_handle(tft, fire);
    // // Hiển thị người dùng
    // user_handle(tft, user_data, north_offset, imu_data);
    // // Hiển thị thông tin
    // lcd_setup_reality_text_outline(tft);
    // lcd_update_reality_text_outline(tft, valve_open_status, user_data);
}


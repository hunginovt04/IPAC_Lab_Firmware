#include "create_msg.h"

void get_training_msg(RSSI_Data *wifi_rssi_data, RSSI_Data *ble_rssi_data,
                      IMU_Data *imu_data, String *message)
{
    *message = String(wifi_rssi_data[0].rssi) + ";" +
               String(wifi_rssi_data[1].rssi) + ";" +
               String(wifi_rssi_data[2].rssi) + ";" +
               String(wifi_rssi_data[3].rssi) + ";" +
               String(ble_rssi_data[0].rssi) + ";" +
               String(ble_rssi_data[1].rssi) + ";" +
               String(ble_rssi_data[2].rssi) + ";" +
               String(ble_rssi_data[3].rssi) + ";" +
               String(imu_data->acc.x) + ";" +
               String(imu_data->acc.y) + ";" +
               String(imu_data->acc.z) + ";" +
               String(imu_data->gyro.x) + ";" +
               String(imu_data->gyro.y) + ";" +
               String(imu_data->gyro.z) + ";" +
               String(imu_data->mag.x) + ";" +
               String(imu_data->mag.y) + ";" +
               String(imu_data->mag.z) + ";" +
               String(imu_data->euler.x) + ";" +
               String(imu_data->euler.y) + ";" +
               String(imu_data->euler.z);
}

void get_training_msg_v2(RSSI_Data *wifi_rssi_data, RSSI_Data *ble_rssi_data,
                         IMU_Data *imu_data, String *message)
{
    *message = "{\"rssi_wifi_1\": " + String(wifi_rssi_data[0].rssi) +
               ",\"rssi_wifi_2\": " + String(wifi_rssi_data[1].rssi) +
               ",\"rssi_wifi_3\": " + String(wifi_rssi_data[2].rssi) +
               ",\"rssi_wifi_4\": " + String(wifi_rssi_data[3].rssi) +
               ",\"rssi_ble_1\": " + String(ble_rssi_data[0].rssi) +
               ",\"rssi_ble_2\": " + String(ble_rssi_data[1].rssi) +
               ",\"rssi_ble_3\": " + String(ble_rssi_data[2].rssi) +
               ",\"rssi_ble_4\": " + String(ble_rssi_data[3].rssi) +
               ",\"magnetic_field_y\": " + String(imu_data->mag.y) +
               ",\"magnetic_field_z\": " + String(imu_data->mag.z) + "}";
}

void get_real_msg(RSSI_Data *wifi_rssi_data, RSSI_Data *ble_rssi_data,
                  IMU_Data *imu_data, int *valve_status, bool *mode_status,
                  String *message, unsigned long *time)
{
    *message = String(wifi_rssi_data[0].rssi) + "," +
               String(wifi_rssi_data[1].rssi) + "," +
               String(wifi_rssi_data[2].rssi) + "," +
               String(wifi_rssi_data[3].rssi) + "," +
               String(ble_rssi_data[0].rssi) + "," +
               String(ble_rssi_data[1].rssi) + "," +
               String(ble_rssi_data[2].rssi) + "," +
               String(ble_rssi_data[3].rssi) + "," +
               String(imu_data->acc.x) + "," +
               String(imu_data->acc.y) + "," +
               String(imu_data->acc.z) + "," +
               String(imu_data->gyro.x) + "," +
               String(imu_data->gyro.y) + "," +
               String(imu_data->gyro.z) + "," +
               String(imu_data->mag.x) + "," +
               String(imu_data->mag.y) + "," +
               String(imu_data->mag.z) + "," +
               String(imu_data->euler.x) + "," +
               String(imu_data->euler.y) + "," +
               String(imu_data->euler.z) + "," +
               String(*valve_status) + "," +
               String(*mode_status) + "," +
               String(*time);
}

void get_infor_msg(String training_topic, String real_topic, int device_id, String *message)
{
    *message = String(device_id) + "," +
               training_topic + "," +
               real_topic;
}

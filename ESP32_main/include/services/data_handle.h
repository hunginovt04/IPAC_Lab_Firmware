#ifndef DATA_HANDLE_H
#define DATA_HANDLE_H

#include "config.h"
#include "ui/lcd_obj.h"


extern String device_payload_buffer;

void handle_user_topic(const char* payload);

void handle_fire_topic(const char* payload);

void handle_map_topic(const char* payload);

void nozzel_device_packing_mqtt_payload(IMU_Data &imu_data, Valve_Data &valve_data, String &device_payload_buffer);

void extinguisher_device_packing_mqtt_payload(IMU_Data &imu_data, Valve_Data &valve_data, String &device_payload_buffer);
#endif
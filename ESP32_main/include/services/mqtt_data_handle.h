#ifndef MQTT_DATA_HANDLE_H
#define MQTT_DATA_HANDLE_H

#include <config.h>

void handle_map_data_topic(const char* payload);
void handle_user_data_topic(const char* payload);
void handle_fire_data_topic(const char* payload);

#endif // MQTT_DATA_HANDLE_H
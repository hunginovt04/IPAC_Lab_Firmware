#include "services/mqtt_data_handle.h"

Map_data map_data;
float north_offset = 0;
int fire_map[MAP_WIDTH_MAX][MAP_HEIGHT_MAX];
User_data user_data;
int fire_num = 0;

void reset_map(int a[MAP_WIDTH_MAX][MAP_HEIGHT_MAX])
{
    for (int i = 0; i < MAP_WIDTH_MAX; i++)
    {
        for (int j = 0; j < MAP_HEIGHT_MAX; j++)
        {
            a[i][j] = 0;
        }
    }
}

void handle_map_data_topic(const char *payload)
{
    reset_map(map_data.map_cells);
    JsonDocument doc;
    // Parse JSON
    DeserializationError error = deserializeJson(doc, payload);
    if (error)
    {
        Serial.print("Map_data JSON parse failed: ");
        Serial.println(error.c_str());
        return;
    }
    map_data.width = doc["info"]["x"];
    map_data.height = doc["info"]["y"];
    north_offset = doc["info"]["north_offset"];
    JsonArray passable_array = doc["cells"];

    for (JsonArray cell : passable_array)
    {
        int_Coordinate coord;
        coord.x = cell[0];
        coord.y = cell[1];
        map_data.map_cells[coord.x][coord.y] = 1; // Mark passable cells in the map
    }
};
void handle_user_data_topic(const char *payload)
{
    JsonDocument doc;
    // Parse JSON
    DeserializationError error = deserializeJson(doc, payload);
    if (error)
    {
        Serial.print("User_data JSON parse failed: ");
        Serial.println(error.c_str());
        return;
    }
    user_data.user_x = doc["x"];
    user_data.user_y = doc["y"];
    user_data.user_score = doc["score"];
};
void handle_fire_data_topic(const char *payload)
{
    reset_map(fire_map);
    JsonDocument doc;
    // Parse JSON
    DeserializationError error = deserializeJson(doc, payload);
    if (error)
    {
        Serial.print("Fire_data JSON parse failed: ");
        Serial.println(error.c_str());
        return;
    }
    fire_num = doc["fires_num"];
    JsonArray fires_array = doc["fires"];
    for (JsonObject fire : fires_array)
    {
        Fire_data fire_data;
        fire_data.fire_x = fire["x"];
        fire_data.fire_y = fire["y"];
        fire_data.fire_lvl = fire["level"];
        fire_map[fire_data.fire_x][fire_data.fire_y] = fire_data.fire_lvl; // Mark fire level in the map
    }
};


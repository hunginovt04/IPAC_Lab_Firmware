#include "read_valve_data.h"

void read_valve_open_status(int *valve_open_status, bool* mode_status)
{
    int raw_value = analogRead(VALVE_PIN);

    // Convert ADC value to opening percentage
    *valve_open_status = (int)((raw_value / 700.0) * 100);

    // Limit the result to the range 0 - 100%
    if (*valve_open_status > 100)
    {
        *valve_open_status = 100;
    }
    else if (*valve_open_status < 0)
    {
        *valve_open_status = 0;
    }
    if(*valve_open_status > 0) *mode_status = 1;
}
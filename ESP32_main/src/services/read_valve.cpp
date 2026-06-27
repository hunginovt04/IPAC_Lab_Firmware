#include "services/read_valve.h"

void init_valve(void)
{
    pinMode(VALVE_STATUS_PIN, INPUT);
    pinMode(VALVE_MODE_PIN, INPUT);
}
void read_valve_open_status(int *valve_open_status, int *mode_status)
{
    int raw_value = analogRead(VALVE_STATUS_PIN);

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
    if (*valve_open_status > 0)
        *mode_status = 1;
}
void read_valve_mode(void) {
    int raw_value = analogRead(VALVE_MODE_PIN);
};
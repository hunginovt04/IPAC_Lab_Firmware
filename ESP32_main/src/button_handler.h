#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

// Libraries
#include <Arduino.h>
#include "config.h"

void button_and_valve_init();
// Check mode of system:
bool is_sw2_on(); // True for Training mode and False for Reality Mode

bool is_sw1_on(); // True for Training/Reality Mode and Flase for Default Mode

#endif
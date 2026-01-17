#pragma once

#include <Arduino.h>
#include <vl53l4cd_class.h>
#include "config/pins.h"
#include "config/config.h"

extern VL53L4CD sensor_front;
extern VL53L4CD sensor_r90;
extern VL53L4CD sensor_r45;
extern VL53L4CD sensor_l45;
extern VL53L4CD sensor_l90;

extern VL53L4CD *SENSORS[NUM_TOF];
extern const int XSHUTS[NUM_TOF];
extern const char *NAMES[NUM_TOF];
extern const uint8_t ADDR8[NUM_TOF];
extern const uint16_t BUDGET_MS[NUM_TOF];
extern const uint16_t PERIOD_MS[NUM_TOF];
extern const uint8_t POLL_ORDER[NUM_TOF];
extern const uint8_t START_ORDER[NUM_TOF];

void initTofSensors();

#pragma once

#include <stdint.h>
#include "../config/config.h"

// Robot state structure containing all sensor data
struct Robot {
    uint16_t g_dist_mm[NUM_TOF];  // Distance measurements from ToF sensors
    uint8_t g_status[NUM_TOF];     // Status codes for each sensor (0 = OK)
};

// Global robot instance - declared here, defined in main.cpp
extern Robot robot;
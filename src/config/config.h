#pragma once

#include <Wire.h>

#define STATE_STRING_SIZE 128

// ===== WIFI config =====
#define WIFI_SSID       "Teshan's"
#define WIFI_PASSWORD   "teshan123"

// ===== I2C config =====
#define DEV_I2C        Wire
#define DEV_I2C_OBJ    DEV_I2C
#define DEV_I2C1      Wire1
#define DEV_I2C1_OBJ  DEV_I2C1
#define I2C_SPEED      400000   // drop to 100000 if wiring is long/noisy

#define NUM_TOF 5

// ===== ST driver expects 8-bit addresses (scanner shows 7-bit = addr8 >> 1) =====
#define ADDR_FRONT_8B    0x54  // 7-bit 0x2A
#define ADDR_RIGHT90_8B  0x56  // 7-bit 0x2B
#define ADDR_RIGHT45_8B  0x58  // 7-bit 0x2C
#define ADDR_LEFT45_8B   0x5A  // 7-bit 0x2D
#define ADDR_LEFT90_8B   0x5C  // 7-bit 0x2E

// ===== Per-sensor timing (continuous) =====
// Budget for all (ms)
#define BUDGET_MS_DEFAULT  12

// Inter-measurement period per sensor (ms)
#define PERIOD_FRONT_MS    12
#define PERIOD_RIGHT90_MS  13
#define PERIOD_RIGHT45_MS  14
#define PERIOD_LEFT45_MS   15
#define PERIOD_LEFT90_MS   16


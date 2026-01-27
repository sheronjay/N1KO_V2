#pragma once
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include "config/config.h"
#include "config/pins.h"

extern SemaphoreHandle_t g_i2cMutex;

void initSystemResources();

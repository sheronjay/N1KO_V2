#pragma once

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hardware/tof.h"
#include "system/systemResources.h"
#include "utility/state.h"


void rangerTask(void *);
void tofTask();
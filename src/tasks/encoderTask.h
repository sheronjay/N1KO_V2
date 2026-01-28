#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"

#include <stdint.h>
#include <Arduino.h>
#include "AS5600.h"
#include "hardware/encoder.h"
#include "system/systemResources.h"
#include "config/config.h"

#include "utility/state.h"

void encoderTask();

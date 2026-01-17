#include "systemResources.h"

SemaphoreHandle_t g_i2cMutex = NULL;

void initSystemResources() {
    g_i2cMutex = xSemaphoreCreateMutex();

    // Optional safety check
    configASSERT(g_i2cMutex != NULL);
}

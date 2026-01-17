#include "systemResources.h"

SemaphoreHandle_t g_i2cMutex = NULL;

void initSystemResources() {
    DEV_I2C.begin();
    DEV_I2C.setClock(I2C_SPEED);
    g_i2cMutex = xSemaphoreCreateMutex();

    // Optional safety check
    configASSERT(g_i2cMutex != NULL);

}

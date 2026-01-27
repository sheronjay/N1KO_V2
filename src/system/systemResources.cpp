#include "systemResources.h"

SemaphoreHandle_t g_i2cMutex = NULL;

void initSystemResources() {
    DEV_I2C.begin();
    DEV_I2C.setClock(I2C_SPEED);
    DEV_I2C1_OBJ.begin(I2C_second_bus_SDA, I2C_second_bus_SCL, I2C_SPEED);
    g_i2cMutex = xSemaphoreCreateMutex();

    // Optional safety check
    configASSERT(g_i2cMutex != NULL);

}

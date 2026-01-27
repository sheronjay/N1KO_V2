#include "encoder.h"

// Encoder instances
AS5600 as5600_0(&DEV_I2C);
AS5600 as5600_1(&DEV_I2C1);


void encoder_init(){
    Serial.print("Connect encoder 0: ");
    Serial.println(as5600_0.isConnected() ? "true" : "false");
    delay(500);

    Serial.print("Connect encoder 1: ");
    Serial.println(as5600_1.isConnected() ? "true" : "false");
    delay(500);

    if (!as5600_0.isConnected() || !as5600_1.isConnected())
    {
        Serial.println("One or both encoders not connected. Check wiring.");
        while (1)
        vTaskDelay(pdMS_TO_TICKS(1000)); // halt task
    }
}


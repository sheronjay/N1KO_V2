#include "tofTask.h"

// Ranger task - continuously polls ToF sensors and updates robot state
void rangerTask(void *)
{
  for (;;)
  {
    for (uint8_t k = 0; k < NUM_TOF; ++k)
    {
      int idx = POLL_ORDER[k];
      uint8_t ready = 0;

      // Check → (maybe) read → clear; DO NOT stop ranging (continuous mode)
      xSemaphoreTake(g_i2cMutex, portMAX_DELAY);
      bool ok = (SENSORS[idx]->VL53L4CD_CheckForDataReady(&ready) == 0) && ready;
      if (ok)
      {
        VL53L4CD_Result_t r;
        if (SENSORS[idx]->VL53L4CD_GetResult(&r) == 0)
        {
          robot.g_dist_mm[idx] = r.distance_mm;
          robot.g_status[idx] = r.range_status; // 0=OK
        }
        SENSORS[idx]->VL53L4CD_ClearInterrupt(); // arm next frame
      }
      xSemaphoreGive(g_i2cMutex);

      // Small backoff so we don't hammer I2C; sensors self-cadence anyway
      vTaskDelay(pdMS_TO_TICKS(1));
    }
  }
}

void tofTask()
{
  Serial.println("Creating ToF ranger task...");

  xTaskCreatePinnedToCore(rangerTask, "ToF Ranger Task", 2048, NULL, 1, NULL, 1);
  
  Serial.println("ToF ranger task created.");
}
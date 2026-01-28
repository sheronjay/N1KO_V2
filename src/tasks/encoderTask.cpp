#include "encoderTask.h"


// Left, Right
uint16_t pulses[2];
uint16_t pulses_prev[2];
int pulses_ovf[2];

void update(){
    pulses[0] = as5600_0.readAngle();
    pulses[1] = as5600_1.readAngle();

    for (int i = 0; i < 2; i++) {
      if (pulses[i] > pulses_prev[i] + HALF_CPR) {
        pulses_ovf[i]--;
      } else if (pulses[i] < pulses_prev[i] - HALF_CPR) {
        pulses_ovf[i]++;
      }
      pulses_prev[i] = pulses[i];
    }
}

void updateTicks(){
    robot.g_left_ticks  = (int64_t)pulses_ovf[0] * CPR + pulses[0];
    robot.g_right_ticks = (int64_t)pulses_ovf[1] * CPR + pulses[1];
}

void tickTask(void *pvParameters)
{
  (void)pvParameters;

  for (;;)
  {
    update();
    updateTicks();

    vTaskDelay(pdMS_TO_TICKS(1));      // ~1 kHz
  }
}

void encoderTask()
{
  Serial.println("Creating encoder tick task...");

  xTaskCreatePinnedToCore(tickTask, "EncoderTick", 4096, nullptr, 2, nullptr, 1);

  Serial.println("Encoder tick task created.");
}


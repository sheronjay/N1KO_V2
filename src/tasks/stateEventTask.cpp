#include "stateEventTask.h"

JsonDocument stateJson;

char tempString[STATE_STRING_SIZE];
void getStateString(Robot *robot, char tempString[STATE_STRING_SIZE]);

void TaskEventSourceSender(void* pvParameters) {
  while (WiFi.status() != WL_CONNECTED) {
    vTaskDelay(5000);
  }

  while (true) {
    getStateString(&robot, tempString);
    // Serial.println(tempString);
    sendEventSource("state", tempString);
    vTaskDelay(200);
  }
}

void getStateString(Robot* robot, char tempString[STATE_STRING_SIZE]) {
    // Distance sensors
    for (int i = 0; i < NUM_TOF; i++) {
        stateJson["distances"][i] = robot->g_dist_mm[i];
    }

    serializeJson(stateJson, tempString, STATE_STRING_SIZE);
}

void taskEventSourceSender() {
  vTaskDelay(2000);
  xTaskCreatePinnedToCore(TaskEventSourceSender, "TaskEvent",
                          20000,  // This stack size can be checked & adjusted
                                  // by reading the Stack Highwater
                          NULL,
                          3,  // CRASH if not priority 3 !!!
                          NULL, 0);
}
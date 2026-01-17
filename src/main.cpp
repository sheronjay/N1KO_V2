#include <Wire.h>
#include "utility/state.h"
#include "system/systemInit.h"
#include "tasks/tofTask.h"

// Global robot instance
Robot robot;

void setup(){
    Serial.begin(115200);
    Serial.println("Serial Monitor Initialized");

    // Initialize system resources (mutex, etc.)
    initSystem();
    Serial.println("System Initialized");
    
    // Create ToF polling task
    tofTask();
    Serial.println("ToF Task Created");
}

void loop(){
    // Main loop - FreeRTOS tasks handle ToF polling
    // Add any main loop logic here if needed
    delay(100);
}
#include <Wire.h>
#include "utility/state.h"
#include "system/systemInit.h"
#include "tasks/tofTask.h"
#include "tasks/wifiTask.h"
#include "tasks/webServerTask.h"

// Global robot instance
Robot robot;

void setup(){
    Serial.begin(115200);
    Serial.println("Serial Monitor Initialized");

    // Initialize system resources (mutex, etc.)
    initSystem();
    Serial.println("System Initialized");

    // Create WiFi task
    taskWifi();
    Serial.println("WiFi Task Created");

    // Create Web Server task
    taskWebserver();
    Serial.println("Web Server Task Created");

    // Create ToF polling task
    tofTask();
    Serial.println("ToF Task Created");
}

void loop(){
    // Main loop - FreeRTOS tasks handle ToF polling
    // Print all sensor distances
    Serial.println("=== ToF Sensor Readings ===");
    Serial.printf("Front:    %4d mm (status: %d)\n", robot.g_dist_mm[IDX_FRONT], robot.g_status[IDX_FRONT]);
    Serial.printf("Right90:  %4d mm (status: %d)\n", robot.g_dist_mm[IDX_RIGHT90], robot.g_status[IDX_RIGHT90]);
    Serial.printf("Right45:  %4d mm (status: %d)\n", robot.g_dist_mm[IDX_RIGHT45], robot.g_status[IDX_RIGHT45]);
    Serial.printf("Left45:   %4d mm (status: %d)\n", robot.g_dist_mm[IDX_LEFT45], robot.g_status[IDX_LEFT45]);
    Serial.printf("Left90:   %4d mm (status: %d)\n", robot.g_dist_mm[IDX_LEFT90], robot.g_status[IDX_LEFT90]);
    Serial.println();
    
    delay(1000);
}
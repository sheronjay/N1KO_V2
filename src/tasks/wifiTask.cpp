#include "wifiTask.h"
void TaskWifi(void* pvParameters) {
    vTaskDelay(200);
    WiFi.mode(WIFI_STA);
    WiFi.setAutoReconnect(true);
    WiFi.persistent(false); // don't keep writing creds to flash

    while (true)
    {
        if (WiFi.status() != WL_CONNECTED)
        {
            Serial.print("Connecting to WiFi: ");
            Serial.println(WIFI_SSID);

            WiFi.disconnect(true); // reset previous state
            vTaskDelay(pdMS_TO_TICKS(200));
            WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

            // Wait up to ~10 seconds (50 * 200ms)
            int tries = 0;
            while (WiFi.status() != WL_CONNECTED && tries++ < 50)
            {
                vTaskDelay(pdMS_TO_TICKS(200));
                Serial.print(".");
            }
            Serial.println();

            if (WiFi.status() == WL_CONNECTED)
            {
                Serial.print("WiFi connected. IP: ");
                Serial.println(WiFi.localIP());
                Serial.print("RSSI: ");
                Serial.println(WiFi.RSSI());
            }
            else
            {
                Serial.println("WiFi connect failed, retrying in 2s...");
                vTaskDelay(pdMS_TO_TICKS(2000));
            }
        }
        else
        {
            // Connected: just monitor occasionally
            vTaskDelay(pdMS_TO_TICKS(5000));
        }
  }
}

void taskWifi() {
  xTaskCreatePinnedToCore(
    TaskWifi,
    "TaskWifi",
    8192,
    nullptr,
    0,        // low priority is fine
    nullptr,
    1
  );
}

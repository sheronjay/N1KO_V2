#include "webServerTask.h"

AsyncWebServer server(80);
AsyncEventSource events("/events");

void notFound(AsyncWebServerRequest* request) {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += request->url();
  message += "\nMethod: ";
  message += (request->method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += request->args();
  message += "\n";
  for (uint8_t i = 0; i < request->args(); i++) {
    message += " " + request->argName(i) + ": " + request->arg(i) + "\n";
  }
  request->send(404, "text/plain", message);
}

void TaskWebserver(void* pvParameters) {
    while ((WiFi.status() != WL_CONNECTED || WiFi.localIP() == INADDR_NONE) &&
        WiFi.softAPIP() == INADDR_NONE) {
        vTaskDelay(5000);
  }

  (void)pvParameters;

  server.onNotFound(notFound);
  server.addHandler(&events);
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server.begin();
  Serial.println("HTTP server started");

  while (true) {
    vTaskDelay(24 * 3600 * 1000);
  }
}

void sendEventSource(const char* event, char* data) {
  events.send(data, event, millis());
}

void taskWebserver() {
  vTaskDelay(4351);
  // Now set up two tasks to run independently.
  xTaskCreatePinnedToCore(TaskWebserver, "TaskWebserver",
                          5000,  // This stack size can be checked &
                                 // adjusted by reading the Stack Highwater
                          NULL,
                          0,  // Priority, with 3 (configMAX_PRIORITIES - 1)
                              // being the highest, and 0 being the lowest.
                          NULL, 0);
}
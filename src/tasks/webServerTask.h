#include <ESPAsyncWebServer.h>
#include <WiFi.h>

void sendEventSource(const char *event, char *data);
void taskWebserver();
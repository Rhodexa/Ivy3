#pragma once

#include <WebServer.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include "nutsnbolts.h"


// Declare things here
extern WebServer server;

extern const char* ssid;
extern const char* password;

extern IPAddress local_IP;
extern IPAddress gateway;
extern IPAddress subnet;
extern IPAddress primaryDNS;
extern IPAddress secondaryDNS;

void setupWebServer();
void connectToWiFi();
void ui_begin();
void ui_loop();

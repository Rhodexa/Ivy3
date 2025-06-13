#include "ui.h"
#include "page.h"

void pushHistoryToJson(JsonArray arr, const int* data, int len) {
  for (int i = 0; i < len; ++i) {
    arr.add(data[i]);
  }
}

void printOutletsToJson(JsonArray arr) {
  for (int i = 0; i < N_OUTLETS; ++i) {
    JsonObject obj = arr.createNestedObject();
    obj["label"] = outlet[i].name;
    obj["state"] = outlet[i].current_state;
    obj["mode"] = outlet[i].mode;
  }
}

/* Actual sauce */

WebServer server(80);

const char* ssid = "Zooey";
const char* password = "19731973";
// const char* ssid = "TP-Link_BC20";
// const char* password = "18753486";

IPAddress local_IP(192, 168, 1, 34);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   // Google's DNS
IPAddress secondaryDNS(1, 1, 1, 1); // Cloudflare's DNS


// ======= Function: Serve Monitoring Page =======
void setupWebServer() {
  // Root
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", page);
  });

  // Sensors
  server.on("/status", HTTP_GET, []() {
    StaticJsonDocument<2048> doc;
    doc["ntp"] = ntp_ok;

    // Clock
    char clockStr[6];
    snprintf(clockStr, sizeof(clockStr), "%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);
    doc["clock"] = clockStr;

    // Temp
    auto temp = doc["temp"].to<JsonObject>();
    temp["current"] = sensors.temperature;
    auto tempLog = temp["log"].to<JsonObject>();
    pushHistoryToJson(tempLog.createNestedArray("last_24_hours"), tempHistory24h, CHART_LAST_INDEX_24H + 1);
    pushHistoryToJson(tempLog.createNestedArray("last_hour"), tempHistory1h, CHART_LAST_INDEX_1H + 1);
    pushHistoryToJson(tempLog.createNestedArray("last_5_minutes"), tempHistory5m, CHART_LAST_INDEX_5M + 1);

    // Humidity
    auto humidity = doc["humidity"].to<JsonObject>();
    humidity["current"] = sensors.humidity;
    auto humLog = humidity["log"].to<JsonObject>();
    pushHistoryToJson(humLog.createNestedArray("last_24_hours"), humidityHistory24h, CHART_LAST_INDEX_24H + 1);
    pushHistoryToJson(humLog.createNestedArray("last_hour"), humidityHistory1h, CHART_LAST_INDEX_1H + 1);
    pushHistoryToJson(humLog.createNestedArray("last_5_minutes"), humidityHistory5m, CHART_LAST_INDEX_5M + 1);

    // Outlets
    JsonArray outlets = doc.createNestedArray("outlets");
    printOutletsToJson(outlets); // Adjust this one too to push directly

    String output;
    serializeJson(doc, output);
    server.send(200, "application/json", output);
  });

  /* Button Racks for each Outlet */
  server.on("/mode", []() {
    if (server.hasArg("index") && server.hasArg("mode")) {
      int index = server.arg("index").toInt();
      int mode = server.arg("mode").toInt();

      if (index >= 0 && index < N_OUTLETS) {
        outlet[index].mode = mode;
        server.send(200, "text/plain", "Mode updated");
      } else {
        server.send(400, "text/plain", "(mode) Invalid index");
      }
    } else {
      server.send(400, "text/plain", "(mode) Missing parameters");
    }
  });

  server.on("/switch", []() {
    if (server.hasArg("index") && server.hasArg("state")) {
      int index = server.arg("index").toInt();
      int state = server.arg("state").toInt();

      if (index >= 0 && index < N_OUTLETS) {
        outlet[index].current_state = state;
        server.send(200, "text/plain", "Switch updated");
      } else {
        server.send(400, "text/plain", "(state) Invalid index");
      }
    } else {
      server.send(400, "text/plain", "(state) Missing parameters");
    }
  });

  server.begin();
  Serial.println("Web server started");
}


// ======= Function: Connect to Wi-Fi =======
void connectToWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to Wi-Fi: "); Serial.println(ssid);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(100);
    Serial.print(".");
    attempts ++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWi-Fi Connected!");
    Serial.print("Local IP: "); Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWi-Fi Connection Failed!");
  }
}

// ======= WiFi Begin Wrapper =======
void ui_begin() {
  connectToWiFi();
  setupWebServer();
}

// ======= WiFi Loop Wrapper =======
void ui_loop() {
  server.handleClient();
}
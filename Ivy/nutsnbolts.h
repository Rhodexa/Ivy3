#pragma once
#include "outlet.h"
#include "time.h"

extern const int N_OUTLETS;
extern Outlet outlet[];  // or Outlet* outlet;

constexpr int CHART_LAST_INDEX_24H = 23;
constexpr int CHART_LAST_INDEX_1H = 59;
constexpr int CHART_LAST_INDEX_5M = 39;
extern int humidityHistory24h[CHART_LAST_INDEX_24H + 1];
extern int humidityHistory1h[CHART_LAST_INDEX_1H + 1];
extern int humidityHistory5m[CHART_LAST_INDEX_5M + 1];
extern int tempHistory24h[CHART_LAST_INDEX_24H + 1];
extern int tempHistory1h[CHART_LAST_INDEX_1H + 1];
extern int tempHistory5m[CHART_LAST_INDEX_5M + 1];

struct Sensors{
  int temperature;
  int humidity;
};
extern Sensors sensors;

extern struct tm timeinfo;
extern int ntp_ok;
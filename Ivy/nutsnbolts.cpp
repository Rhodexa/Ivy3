#include "nutsnbolts.h"

/* Outlets */
const int N_OUTLETS = 8;
Outlet outlet[N_OUTLETS] = {
  Outlet(16, "Toma 0"),
  Outlet(17, "Toma 1"),
  Outlet(18, "Toma 2"),
  Outlet(29, "Toma 3"),
  Outlet(21, "Toma 4"),
  Outlet(22, "Toma 5"),
  Outlet(23, "Toma 6"),
  Outlet(25, "Toma 7")
};

/* Time charts */
int humidityHistory24h[CHART_LAST_INDEX_24H + 1];
int humidityHistory1h[CHART_LAST_INDEX_1H + 1];
int humidityHistory5m[CHART_LAST_INDEX_5M + 1];
int tempHistory24h[CHART_LAST_INDEX_24H + 1];
int tempHistory1h[CHART_LAST_INDEX_1H + 1];
int tempHistory5m[CHART_LAST_INDEX_5M + 1];

/* Sensors */
Sensors sensors;

/* Time info */
struct tm timeinfo;
int ntp_ok = 0;
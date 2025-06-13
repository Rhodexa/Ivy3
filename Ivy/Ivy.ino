/*
  Dependencies:
    DHT Adafruit library
    ArduinoJSON
*/


#include "ArduinoOTA.h"
#include "nutsnbolts.h"
#include "ui.h"
#include "time.h"
#include "DHT.h"

DHT dht(4, DHT11);

/*/////////////////////////////////////////////////// Mi oficina // */
int sensor_update_seconds_counter = 0;
int ntp_update_timer = 0;
void updateSensors(){
  if(sensor_update_seconds_counter > 9){
    sensor_update_seconds_counter = 0;

    ntp_update_timer++;
    if(ntp_update_timer > 360){
      ntp_ok = getLocalTime(&timeinfo);
      ntp_update_timer = 0;
    }

    float t = dht.readTemperature();
    if (!isnan(t)) sensors.temperature = (int)t;
    //else sensors.temperature = 65535;
    else sensors.temperature = random(40);

    float h = dht.readHumidity();
    if (!isnan(h)) sensors.humidity = (int)h;
    //else sensors.humidity = 65535;
    else sensors.humidity = random(40);

  } 
}

int valid(int val) { return val == 65535 ? 0 : val; }
void ivyChartsUpdate() {
  int current_second = timeinfo.tm_sec;
  int current_minute = timeinfo.tm_min;
  int current_hour = timeinfo.tm_hour;
  static int last_minute = -1;
  static int last_hour = -1;
  static int last_second = -1;
  static int seconds_counter = 0;

  // every second
  seconds_counter++;
  if(seconds_counter > 7) { // every 8 seconds
    seconds_counter = 0;
    for (int i = 0; i < CHART_LAST_INDEX_5M; i++) {
      tempHistory5m[i] = tempHistory5m[i + 1];
      humidityHistory5m[i] = humidityHistory5m[i + 1];
    }
    tempHistory5m[CHART_LAST_INDEX_5M] = valid(sensors.temperature);
    humidityHistory5m[CHART_LAST_INDEX_5M] = valid(sensors.humidity);
  }

  // every minute
  if (current_minute != last_minute) { 
    last_minute = current_minute;
    for (int i = 0; i < CHART_LAST_INDEX_1H; i++) {
      tempHistory1h[i] = tempHistory1h[i + 1];
      humidityHistory1h[i] = humidityHistory1h[i + 1];
    }
    tempHistory1h[CHART_LAST_INDEX_1H] = valid(sensors.temperature);
    humidityHistory1h[CHART_LAST_INDEX_1H] = valid(sensors.humidity);    
  }

  if (current_hour != last_hour) {
    last_hour = current_hour;
    for (int i = 0; i < CHART_LAST_INDEX_24H; i++) {
      tempHistory24h[i] = tempHistory24h[i + 1];
      humidityHistory24h[i] = humidityHistory24h[i + 1];
    }
    tempHistory24h[CHART_LAST_INDEX_24H] = valid(sensors.temperature);
    humidityHistory24h[CHART_LAST_INDEX_24H] = valid(sensors.humidity);    
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  ui_begin();

  ArduinoOTA.begin();
  ArduinoOTA.setPassword("1234");

  IPAddress testIP;
  if (!WiFi.hostByName("pool.ntp.org", testIP)) {
    Serial.println("DNS lookup failed!");
  } else {
    Serial.print("DNS resolved pool.ntp.org to: ");
    Serial.println(testIP);
  }

  configTime(-3600*3, 0, "pool.ntp.org", "time.nist.gov", "time.google.com");

  Serial.println("Waiting for NTP time...");
  int attempts = 0;
  while (!getLocalTime(&timeinfo) && attempts++ < 10) {
    Serial.println("NTP not yet available...");
    delay(1000);
  }
  if (attempts >= 10) {
    Serial.println("NTP sync failed!");
    digitalWrite(LED_BUILTIN, 1);  // Your LED error handler
  } else {
    Serial.println("NTP sync successful:");
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
    ntp_ok = 1;
  }
  
  onConfig();
}

auto current_millis = millis();
auto last_millis = millis();
void loop() {
  ArduinoOTA.handle();
  ui_loop();
  updateSensors();
  current_millis = millis();
  if(current_millis - last_millis >= 1000) {
    last_millis = current_millis;
    sensor_update_seconds_counter++;
    ivyChartsUpdate();
    onLogic();
    for (int i = 0; i < N_OUTLETS; i++) {
      outlet[i].update();
    }
  }
}






/*/////////////////////////////////////////////////// Tu oficina // */

/*//// Herramientas // */

bool entre_horas(int a, int b) {
  if (a <= b){
    return (a <= timeinfo.tm_hour) && (timeinfo.tm_hour < b);
  }
  return (timeinfo.tm_hour >= a) || (timeinfo.tm_hour < b);
}

// Un poco de azúcar sintáctica

const int SI = 1;
const int NO = 0;

#define TEMPERATURA sensors.temperature
#define HUMEDAD sensors.humidity
#define HORA    timeinfo.tm_hour
#define MINUTO  timeinfo.tm_min
#define SEGUNDO timeinfo.tm_sec

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Acá podés configurar el nombre de las salidas que aparecen en la interfáz gráfica
void onConfig() {
  outlet[0].rename("Luces x3");
  outlet[1].rename("Luces x2");
  outlet[2].rename("Ventilador");
  outlet[3].rename("Extractor");
  outlet[4].rename("Humidificador");
  // outlet[5].raname(" ");
  // outlet[6].raname(" ");
  // outlet[7].raname(" ");
}

// Apodos para adaptar los idiomas!
// Además es más facil decir 'LUCES = SI;' que 'outlet[0].auto_state = 1;'
#define LUCES_2          outlet[0].target_state
#define LUCES_1          outlet[1].target_state
#define VENTILADOR       outlet[2].target_state
#define EXTRACTOR        outlet[3].target_state
#define VEGE_LUCES       outlet[4].target_state
#define VEGE_VENTILADOR  outlet[5].target_state

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Vos te encargás de la logica, yo me encargo del resto
void onLogic()
{
  // 2
  LUCES_1 = entre_horas(21, 9);

  // 3
  LUCES_2 = entre_horas(23, 7);
  
  // 30 minutos cada dos horas
  VENTILADOR = (HORA % 1 == 0) && (MINUTO < 30);

  // 30 minutos cada cuatro horas
  EXTRACTOR = (HORA % 3 == 0) && (MINUTO < 30);

  // Humidificador 
  // if (sensors.humidity > 80) HUMIDIFICADOR = NO;
  // if (sensors.humidity < 60) HUMIDIFICADOR = SI;
}



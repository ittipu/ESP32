#include <WiFi.h>
#include "time.h"

// Replace with your network credentials
const char* ssid = "BRACNet_Employee";
const char* password = "a$UJ@n@pB@ngl@d3$h";
const char* ntpServer = "pool.ntp.org";


unsigned long epochTime;

void setup() {
  Serial.begin(115200);
  initWiFi();
  configTime(0, 0, ntpServer);
}

void loop() {
  epochTime = getTime();
  Serial.print("Epoch Time: ");
  Serial.println(epochTime);
  delay(1000);
}

// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return (0);
  }
  time(&now);
  return now;
}

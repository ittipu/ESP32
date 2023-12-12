#include <WiFi.h>
#include <ESP32Ping.h>

#define WIFI_NAME "IoT"
#define WIFI_PASS "tipu1234@"
// #define WIFI_NAME "tipu"
// #define WIFI_PASS "tipu1234"
#define PING_HOST "google.com"
#define PING_TIME 3

void setup() {
  Serial.begin(115200);
  setup_wifi();
}

void loop() {
  if (Ping.ping(PING_HOST)) {
    Serial.println("Success!!");
  } else {
    Serial.println("Error :(");
  }
  delay(1000);
}


void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_NAME);
  WiFi.begin(WIFI_NAME, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
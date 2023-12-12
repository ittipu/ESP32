#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include "time.h"
const char* ntpServer = "pool.ntp.org";


#include "DHT.h"

#define WIFI_NAME "BRACNet_Employee"
#define WIFI_PASS "a$UJ@n@pB@ngl@d3$h"
// #define WIFI_NAME "tipu"
// #define WIFI_PASS "tipu1234"
// #define MQTT_BROKER "172.16.0.246"
#define MQTT_BROKER "test.mosquitto.org"
#define MQTT_PORT 1883
// #define MQTT_USERNAME "tipu"
// #define MQTT_PASSWORD "tipu"

#define INTERVAL_MAIN_LOOP 5000
#define TOPIC_PUB_TEMP_HUM "bracnet/device1"
#define TOPIC_PUB_DEVICE_BOOT_SUCCESS "esp32/boot/status"
#define TOPIC_SUB_FOR_LED "esp32/led"

#define DHTPIN 15
#define DHTTYPE DHT22

StaticJsonDocument<256> doc;
DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastReadingTime = 0;
const unsigned long readingInterval = INTERVAL_MAIN_LOOP;
unsigned long epochTime;


void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
}

void mqtt_reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // if (client.connect("ESP8266Client", MQTT_USERNAME, MQTT_PASSWORD)) {
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      client.subscribe(TOPIC_SUB_FOR_LED);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void setup() {
  Serial.begin(115200);
  Serial.println();
  dht.begin();
  setup_wifi();
  setup_mqtt();
  configTime(0, 0, ntpServer);
}

void loop() {
  if (!client.connected()) {
    mqtt_reconnect();
  }
  unsigned long currentMillis = millis();
  if (currentMillis - lastReadingTime >= readingInterval) {
    lastReadingTime = currentMillis;
    float humidity, temperature;
    // readDHTData(humidity, temperature);
    char buffer[256];
    epochTime = getTime();
    doc["timestamp"] = epochTime;
    doc["Temp"] = String(200.00, 2);
    doc["Hum"] = String(1400.887, 2);
    Serial.println("Getting Sensor Data - ");
    serializeJson(doc, Serial);  // Json show to Serial
    Serial.println();
    Serial.println("Published Successfully");
    serializeJson(doc, buffer);
    client.publish(TOPIC_PUB_TEMP_HUM, buffer);
    Serial.println();
  }
  client.loop();
}



void readDHTData(float& humidity, float& temperature) {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  }
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

void setup_mqtt() {
  delay(100);
  client.setServer(MQTT_BROKER, MQTT_PORT);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT....");

    // if (client.connect("ESP32Client", MQTT_USERNAME, MQTT_PASSWORD)) {
    if (client.connect("ESP8266Client")) {
      client.publish(TOPIC_PUB_DEVICE_BOOT_SUCCESS, "Device Boot Successfully");
      Serial.println("connected");
    } else {
      Serial.print("failed with state ");
      Serial.println(client.state());
      delay(200);
    }
  }
  client.subscribe(TOPIC_SUB_FOR_LED);
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
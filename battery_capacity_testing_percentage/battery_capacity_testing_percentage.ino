#include <esp_adc_cal.h>
#include <Arduino.h>
#define ADC_PIN 35
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFi.h>


#define WIFI_NAME "BRACNet_Employee"
#define WIFI_PASS "a$UJ@n@pB@ngl@d3$h"
#define MQTT_BROKER "192.53.112.207"
#define MQTT_PORT 1883
#define MQTT_USERNAME "tipu"
#define MQTT_PASSWORD "tipu"

#define INTERVAL_MAIN_LOOP 5000
#define TOPIC_PUB_TEMP_HUM "esp32/dht22"
#define TOPIC_PUB_DEVICE_BOOT_SUCCESS "esp32/boot/status"
#define TOPIC_SUB_FOR_LED "esp32/led"

int vref = 1100;

StaticJsonDocument<256> doc;

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastReadingTime = 0;
const unsigned long readingInterval = INTERVAL_MAIN_LOOP;

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
    if (client.connect("ESP8266Client", MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println("connected");
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
  Serial.begin(115200);  // Set console baud rate
  setup_wifi();
  setup_mqtt();
  esp_adc_cal_characteristics_t adc_chars;
  esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);  //Check type of calibration value used to characterize ADC
  if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
    Serial.printf("eFuse Vref:%u mV", adc_chars.vref);
    vref = adc_chars.vref;
  } else if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP) {
    Serial.printf("Two Point --> coeff_a:%umV coeff_b:%umV\n", adc_chars.coeff_a, adc_chars.coeff_b);
  } else {
    Serial.println("Default Vref: 1100mV");
  }
}

void loop() {
  if (!client.connected()) {
    mqtt_reconnect();
  }
  unsigned long currentMillis = millis();
  if (currentMillis - lastReadingTime >= readingInterval) {
    lastReadingTime = currentMillis;
    readBattery();
    Serial.println();
  }
}

void readBattery() {
  uint16_t v = analogRead(ADC_PIN);
  float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);
  String voltage = "Voltage :" + String(battery_voltage, 2) + "V\n";

  // When connecting USB, the battery detection will return 0,
  // because the adc detection circuit is disconnected when connecting USB
  // Serial.println(voltage);
  if (voltage == "0.00") {
    Serial.println("USB is connected, please disconnect USB.");
  }
  char buffer[256];
  doc["voltage"] = voltage;
  Serial.println("Getting Battery Data - ");
  serializeJson(doc, Serial);  // Json show to Serial
  Serial.println();
  Serial.println("Published Successfully");
  serializeJson(doc, buffer);
  client.publish(TOPIC_PUB_TEMP_HUM, buffer);
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

  while (!client.connected()) {
    Serial.println("Connecting to MQTT....");

    if (client.connect("ESP32Client", MQTT_USERNAME, MQTT_PASSWORD)) {
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

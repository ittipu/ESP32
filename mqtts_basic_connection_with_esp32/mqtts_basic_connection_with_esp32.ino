#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "credentials.h"

/** Wifi Credentials **/
#define WIFI_NAME "IoT"
#define WIFI_PASS "tipu1234@"

/** MQTT Credentials **/
#define MQTT_BROKER "iotcrack.com"
#define MQTT_PORT 8883
#define MQTT_USERNAME "tipu"
#define MQTT_PASSWORD "tipu"
#define SUBSCRIBE_TOPIC "subscribe/topic"
#define PUBLISH_TOPIC "publish/topic"
#define QOS 1

WiFiClientSecure espClient;
PubSubClient client(espClient);

// MQTT Callback Function
void mqttCallback(char* topic, byte* message, unsigned int length) {
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

void setup() {
  Serial.begin(115200);
  setup_wifi();
  setup_mqtt();
}

void loop() {
  if (!client.connected()) {
    mqtt_reconnect();
  }
  client.loop();
  delay(100);
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
  espClient.setCACert(ca_cert);
  espClient.setCertificate(client_certificate);
  espClient.setPrivateKey(private_key);
}

void setup_mqtt() {
  delay(100);
  client.setServer(MQTT_BROKER, MQTT_PORT);
  client.setCallback(mqttCallback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT....");

    // if (client.connect("ESP32Client", MQTT_USERNAME, MQTT_PASSWORD)) {
    if (client.connect("ESP32Client", MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println("connected");
    } else {
      Serial.print("failed with state ");
      Serial.println(client.state());
      delay(200);
    }
  }
  client.subscribe(SUBSCRIBE_TOPIC, QOS);
}

void mqtt_reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client", MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println("connected");
      client.subscribe(SUBSCRIBE_TOPIC, QOS);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
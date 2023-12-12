#include "secrets.h"
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"

#define led_pin 2

// The MQTT topics that this device should publish/subscribe
#define AWS_IOT_PUBLISH_TOPIC   "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"

WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(256);

void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.begin(AWS_IOT_ENDPOINT, 8883, net);

  // Create a message handler
  client.onMessage(messageHandler);

  Serial.print("Connecting to AWS IOT");

  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }

  if (!client.connected()) {
    Serial.println("AWS IoT Timeout!");
    return;
  }

  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Connected!");
}

// void publishMessage()
// {
//   StaticJsonDocument<200> doc;
//   doc["time"] = millis();
//   doc["sensor_a0"] = analogRead(0);
//   char jsonBuffer[512];
//   serializeJson(doc, jsonBuffer); // print to client
//   Serial.println();
//   serializeJson(doc, Serial);

//   client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
// }

void messageHandler(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

   StaticJsonDocument<200> doc;
   deserializeJson(doc, payload);
   String message = doc["led_status"];
   if(message == "1"){
    Serial.println("Led HIGH");
    digitalWrite(led_pin, HIGH);
   }
   if(message == "0"){
    Serial.println("LED LOW");
    digitalWrite(led_pin, LOW);
   }
}

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
  connectAWS();
  Serial.println();
}

void loop() {
  Serial.println("Waiting for aws command");
  client.loop();
  delay(1000);
}

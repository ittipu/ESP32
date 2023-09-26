#include <CayenneMQTTESP32.h>
#include <ESP32Ping.h>
#include <WiFi.h>

#define GAS_SENSOR_PIN 32


//const char* ssid = "VM253FA8";  // Your wifi name
//const char* wifiPassword = "j2nmRUzj4uxr"; // Your wifi password
const char* ssid = "VIRUS.COM";  // Your wifi name
const char* wifiPassword = "mnrs996318"; // Your wifi password

const char* username = "db4ba7a0-6c08-11ed-b193-d9789b2af62b"; // cayenee username
const char* password = "ba2a540dc186df5ef33dc0649ccf6e076e4a16e5"; // cayenee password
const char* clientID = "749ba7c0-6d76-11ed-b193-d9789b2af62b"; // cayenee clientID

const char* pingWebsite = "google.com";


unsigned long int wifi_reconnect_timer = 20;


int gasSensorValue = 0;

void setup() {
  Serial.begin(115200);
  pinMode(GAS_SENSOR_PIN, INPUT);
  Serial.println("Checking WiFi Connectivity");
  if (init_wifi()) {
    if (Ping.ping(pingWebsite)) {
      Serial.println("Internet Connected");
      Cayenne.begin(username, password, clientID, ssid, wifiPassword);
    }
  }
}


void loop() {
  if (Ping.ping(pingWebsite)) {
    Serial.println("Device Online");
    gasSensorValue = readGasSensor();
    Serial.print("The value from gas sensor: ");
    Serial.println(gasSensorValue);
    Cayenne.loop();
  }
  
  else {
    Serial.println("No internet");
    Serial.println("Trying to reconnect");
  }
}


int readGasSensor() {
  int value = analogRead(GAS_SENSOR_PIN);
  return value;
}


bool init_wifi() {
  int reconnect_timer = 0;
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, wifiPassword);
  while (WiFi.status() != WL_CONNECTED) {
    reconnect_timer++;
    Serial.print(".");
    delay(500);
    if (reconnect_timer == wifi_reconnect_timer) {
      Serial.println("\nCan't connect to Wifi!");
      Serial.println("Check WiFi Name and Password");
      Serial.println("Reinitializing WiFi.");
      init_wifi();
    }
  }

  Serial.print("WiFi connected to ");
  Serial.println(WiFi.localIP());
  return true;
}

CAYENNE_OUT_DEFAULT()
{
  Cayenne.virtualWrite(1, gasSensorValue);
}

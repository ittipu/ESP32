#include "defination.h"
#include "wifiConfig.h"
#include "mqttConfig.h"
#include <ArduinoJson.h>



StaticJsonDocument<256> doc;

void setup(){
  Serial.begin(115200);
  setup_wifi();
  
}

void loop(){
  if(!mqtt_client.connected()){
    mqtt_reconnect();
  }
}

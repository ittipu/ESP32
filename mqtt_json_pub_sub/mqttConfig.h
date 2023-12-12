#include "defination.h"
#include "wifiConfig.h"
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient mqtt_client(espClient);

void callback(char* topic, byte* message, unsigned int length);
void mqtt_reconnect();

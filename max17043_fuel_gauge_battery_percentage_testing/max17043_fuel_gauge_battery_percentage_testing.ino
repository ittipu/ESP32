#include <Wire.h>
#include <SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h>

#define FUEL_SDA 33  // Define custom SDA pin
#define FUEL_SCL 32  // Define custom SCL pin

SFE_MAX1704X lipo;
TwoWire myWire(0);
double voltage = 0;
double soc = 0;

void setup() {
  Serial.begin(115200);
  myWire.begin(FUEL_SDA, FUEL_SCL);
  lipo.enableDebugging(Serial);

  if (lipo.begin(myWire) == false)  // Connect to the MAX17043 using non-standard wire port
  {
    Serial.println(F("MAX17043 not detected. Please check wiring. Freezing."));
    while (1)
      ;
  }
  lipo.quickStart();
}

void loop() {
  voltage = lipo.getVoltage();
  soc = lipo.getSOC();
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  Serial.print("Percentage: ");
  Serial.print(soc);
  Serial.println(" %");

  delay(1000); 
}
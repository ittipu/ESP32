String incomingData = ""; // for incoming serial data
 
void setup() {
  Serial2.begin(115200); // opens serial port, sets data rate to 115200 bps
}
 
void loop() {
  Serial2.write("Hello");
}

#include "headers.h"

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  dht.begin();
  soilTempSensor.begin();

  WiFi.disconnect();  //Disconnect from previously connected wifi
  Serial.println("\nWifi disconnected");
  delay(100);
  WiFi.mode(WIFI_STA);  //STAtion mode:the ESP8266 connects to an access point

  while (WiFi.status() != WL_CONNECTED)
    // handleWifi();
    connect_wifi();

  mqttClient.setServer(mqtt_server, mqtt_port);
  if (transmissionFlag)
    connectMQTT();
}

void loop() {
  // unsigned long currentTime = millis();
  // int time_elapsed = currentTime - lastTransmissionTime;

  // Serial.println("Time elapsed: " + String(time_elapsed));
  // if (time_elapsed >= 2000) {
  ledBlink();
  mqttClient.loop();
  handleData();
  // lastTransmissionTime = currentTime;
  // }

  //Wait for a new reading from the sensor
  delay(2000);
}
// #include "WString.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "DHT.h"
#include <OneWire.h>
#include <DallasTemperature.h>

// DHT11 sensor
#define DHTPIN D4
#define DHTTYPE DHT11  // DHT 11
DHT dht(DHTPIN, DHTTYPE);

// Soil Moisture sensor-HW080
#define SOIL_MOISTURE_PIN A0
double map(long x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Soil temp sensor- DS18B20
#define ONE_WIRE_BUS D2
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature soilTempSensor(&oneWire);

void ledBlink() {
  bool ledState = 0;  //To store the current state of led
  digitalWrite(LED_BUILTIN, ledState);
  ledState = !ledState;
  delay(100);
  digitalWrite(LED_BUILTIN, ledState);
}

int wifiNum = 0;  //To store the number of networks found in a wifi scan

String wifi_ssid = "My WiFi";
String wifi_pass = "9212461800";

unsigned long lastTransmissionTime = 0;
boolean transmissionFlag = 1;

const char* mqtt_server = "broker.emqx.io";
const char* mqtt_topic = "/thing";
const int mqtt_port = 1883;
const char* clientId = "esp";

int mqtt_req_count = 1;  //To count the number of mqtt requests sent

// WiFi and MQTT client initialization
WiFiClient espClient;
PubSubClient mqttClient(espClient);
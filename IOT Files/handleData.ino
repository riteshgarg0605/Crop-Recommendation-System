void handleData() {
  // double randomDecimal = random(0, 100) / 100.0;
  // double temp = random(0, 100) + randomDecimal;
  // double humidity = random(0, 100) + randomDecimal;

  // Read data from DHT sensor
  double humidity = dht.readHumidity();
  double temp = dht.readTemperature();

  // Read data of Soil moisture
  int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);

  // Convert the analog value to a percentage (assuming a linear sensor)
  double moisturePercentage = map(soilMoistureValue, 666.00, 180.00, 0.00, 100.00);
  moisturePercentage = constrain(moisturePercentage, 0, 100);

  // Read value of soil temperature
  soilTempSensor.requestTemperatures();
  double soilTemp = soilTempSensor.getTempCByIndex(0);

  // Print the moisture percentage
  Serial.println("---------------------");
  Serial.println("Soil Moisture Val: " + String(soilMoistureValue) + ", Soil Moisture %: " + String(moisturePercentage));
  Serial.println("Soil Temp: " + String(soilTemp) + "°C");
  Serial.println("Humidity: " + String(humidity) + "%,  Temperature: " + String(temp) + "°C");

  String jsonString;
  JsonDocument doc;
  doc["Humidity"] = serialized(String(humidity));
  doc["Temperature"] = serialized(String(temp));
  doc["Moisture"] = serialized(String(moisturePercentage));
  doc["SoilTemp"] = serialized(String(soilTemp));

  // Serialize the JSON object to a string
  serializeJson(doc, jsonString);

  // unsigned long currentTime = millis();
  // int time_elapsed = currentTime - lastTransmissionTime;
  // Serial.println("Time elapsed: " + String(time_elapsed));

  sendCommand();
  // if ((time_elapsed >= 2000) && transmissionFlag) {
  if (transmissionFlag) {
    sendMQTT(jsonString);
  }
  // delay(5000);

  // lastTransmissionTime = currentTime;
}
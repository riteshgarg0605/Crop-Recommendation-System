void connectMQTT() {
  int retryCount = 5;
  while (!mqttClient.connected() && retryCount) {
    Serial.print("Attempting MQTT connection...");
    if (mqttClient.connect(clientId)) {
      Serial.println(" MQTT connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" trying again in 2 seconds");
      delay(2000);
      retryCount--;
    }
  }
}

void sendMQTT(String jsonString) {
  if (mqttClient.connected()) {
    mqttClient.publish(mqtt_topic, jsonString.c_str());
    Serial.println("Sent count: " + String(mqtt_req_count++));
  } else {
    connectMQTT();
  }
}
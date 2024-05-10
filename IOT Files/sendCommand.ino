void sendCommand() {
  if (Serial.available() > 0) {    // Check if any command is received from Serial Monitor
    char command = Serial.read();  // Read the command character
    if (command == 's') {
      transmissionFlag = 1;
      Serial.printf("MQTT send command received, Flag: %d\n", transmissionFlag);
      connectMQTT();

    } else if (command == 't') {
      transmissionFlag = 0;
      Serial.printf("MQTT stop command received, Flag: %d\n", transmissionFlag);
      mqttClient.disconnect();
      Serial.println("MQTT diconnected");
    }
  }
}

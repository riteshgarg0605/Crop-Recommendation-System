void wifiScan() {
  WiFi.scanNetworks(false);
  Serial.print("\nWifi scan started ... ");

  // print out Wi-Fi network scan result upon completion
  wifiNum = WiFi.scanComplete();
  if (wifiNum >= 0) {
    Serial.printf("%d network(s) found\n", wifiNum);
    for (int i = 0; i < wifiNum; i++) {
      Serial.printf(" %02d: Ch:%02d (%ddBm) %s\n", i + 1, WiFi.channel(i), WiFi.RSSI(i), WiFi.SSID(i).c_str());
    }
  }
}

void handleWifi() {
  wifiScan();
  Serial.println("\nStored Wifi Credentials:-");
  Serial.printf("SSID: %s, Password: %s\n", wifi_ssid.c_str(), wifi_pass.c_str());
  Serial.print("Do you want to change wifi credentials?(y/n) ");
  while (!Serial.available())
    ;
  char command = Serial.read();  // Read the command character
  while (Serial.available())
    Serial.read();
  Serial.println(command);
  if (command == 'y') {
    inputCreds();
  }
  // Call connect_wifi with the received SSID and password
  connect_wifi();
  WiFi.scanDelete();
}

void inputCreds() {
  bool correctSSID = 0;
  while (correctSSID != 1) {
    Serial.print("\nEnter SSID: ");
    while (!Serial.available())
      ;
    // Read the SSID from the serial port
    wifi_ssid = Serial.readStringUntil('\n');
    wifi_ssid.trim();
    Serial.print("\"" + String(wifi_ssid) + "\"");

    for (int i = 0; i < wifiNum; i++) {
      if (WiFi.SSID(i) == wifi_ssid) {
        correctSSID = 1;
        break;
      }
    }
    correctSSID ?: Serial.print("\nSSID not found");
  }
  Serial.print("\nEnter password: ");
  while (!Serial.available())
    ;
  // Read the password from the serial port
  wifi_pass = Serial.readStringUntil('\n');
  wifi_pass.trim();
  Serial.println("\"" + String(wifi_pass) + "\"");
}

void connect_wifi() {
  // Connect to Wi-Fi network
  Serial.println("Connecting to ssid: " + String(wifi_ssid));
  WiFi.begin(wifi_ssid, wifi_pass);
  int retries = 7;
  while (WiFi.status() != WL_CONNECTED && retries) {
    Serial.print(". ");
    delay(1000);
    retries--;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected successfully!!");
    // Print the IP address
    Serial.print("Local IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi connection failed\n");
  }
}
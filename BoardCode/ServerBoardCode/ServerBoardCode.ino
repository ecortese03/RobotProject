// ESP32_AP_Server.ino

#include <WiFi.h>

const char* ssid = "ESP32-Host";
const char* password = "12345678";

WiFiServer server(3333);  // TCP server on port 3333

void setup() {
  Serial.begin(115200);

  // Start WiFi in Access Point mode
  WiFi.softAP(ssid, password);
  Serial.println("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Start TCP server
  server.begin();
  Serial.println("TCP server started");
}

void loop() {
  WiFiClient client = server.available(); // Listen for incoming clients
  if (client) {
    Serial.println("Client connected");

    while (client.connected()) {
      if (client.available()) {
        String received = client.readStringUntil('\n');
        Serial.print("Received: ");
        Serial.println(received);

        // Echo back
        client.print("Echo: ");
        client.println(received);
      }
    }

    client.stop();
    Serial.println("Client disconnected");
  }
}
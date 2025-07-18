#include <WiFi.h>

const char* ssid = "ESP32-Host";
const char* password = "12345678";

const char* hostIP = "192.168.4.1"; // Default IP of ESP32 AP
const uint16_t port = 3333;

WiFiClient client;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Connect to server
  if (client.connect(hostIP, port)) {
    Serial.println("Connected to server");

    // Send message
    client.println("Hello from client!");
  } else {
    Serial.println("Connection to server failed");
  }
}

void loop() {
  if (client.connected() && client.available()) {
    String response = client.readStringUntil('\n');
    Serial.print("Received: ");
    Serial.println(response);
  }

  delay(1000);
}
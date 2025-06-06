#include <WiFi.h>
#include <HTTPClient.h>
#define livinglight 4
#define livingfan 2
#define bedlight 32
#define bathlight 33

// Replace with your network credentials
const char* ssid = "Redmi Note 11 Pro 5G";
const char* password = "00000000";

// URL to fetch the content
const char* url = "http://slir.lk/ar/group5/status.txt";

void setup() {

  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  // Start Serial for debugging
  Serial.begin(115200);
  Serial.println("Connecting to Wi-Fi...");

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to Wi-Fi!");
  fetchContent();
}

void loop() {
  // Fetch content periodically
  delay(1500);  // Wait for 30 seconds before fetching again
  fetchContent();
}

void fetchContent() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    Serial.println("Sending HTTP GET request...");

    // Make the request
    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.printf("HTTP Response code: %d\n", httpResponseCode);

      // Print response
      String payload = http.getString();
      Serial.println("Response:");
      Serial.println(payload);
      payload.trim();
      if (payload[3] == 'L') {
        digitalWrite(4, HIGH);
      }
      if (payload[3] == 'l') {
        digitalWrite(4, LOW);
      }
      if (payload[3] == 'F') {
        digitalWrite(2, HIGH);
      }
      if (payload[3] == 'f') {
        digitalWrite(2, LOW);
      }
      if (payload[3] == 'B') {
        digitalWrite(32, HIGH);
      }
      if (payload[3] == 'b') {
        digitalWrite(32, LOW);
      }
      if (payload[3] == 'C') {
        digitalWrite(33, HIGH);
      }
      if (payload[3] == 'c') {
        digitalWrite(33, LOW);
      }
    } else {
      Serial.printf("Error in HTTP request. Code: %d\n", httpResponseCode);
    }

    // End HTTP connection
    http.end();
  } else {
    Serial.println("Wi-Fi not connected!");
  }
}

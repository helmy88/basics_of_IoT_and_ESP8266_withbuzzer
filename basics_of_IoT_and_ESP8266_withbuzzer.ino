#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// Replace with your Wi-Fi credentials
const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";

// ThingSpeak details
const char* thingSpeakAddress = "api.thingspeak.com";
const char* writeAPIKey = "your_thingspeak_api_key";

// Pin connected to the buzzer
const int buzzerPin = 2; // You can change this to any GPIO pin

void setup() {
  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Simulate different states using the buzzer
  buzzBuzzer(500, 1000); // Buzz the buzzer for 500ms, delay 1000ms
  sendDataToThingSpeak("State 1");

  delay(3000);

  buzzBuzzer(300, 500);
  sendDataToThingSpeak("State 2");

  delay(3000);

  buzzBuzzer(1000, 200);
  sendDataToThingSpeak("State 3");

  delay(3000);
}

void buzzBuzzer(int onTime, int offTime) {
  digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
  delay(onTime);
  digitalWrite(buzzerPin, LOW); // Turn off the buzzer
  delay(offTime);
}

void sendDataToThingSpeak(String status) {
  WiFiClient client;
  if (client.connect(thingSpeakAddress, 80)) {
    String data = "field1=" + status;
    String request = "POST /update HTTP/1.1\r\n" +
                     "Host: " + String(thingSpeakAddress) + "\r\n" +
                     "Connection: close\r\n" +
                     "X-THINGSPEAKAPIKEY: " + String(writeAPIKey) + "\r\n" +
                     "Content-Type: application/x-www-form-urlencoded\r\n" +
                     "Content-Length: " + String(data.length()) + "\r\n\r\n" +
                     data;
    client.print(request);
    delay(100);
    client.stop();
  }
}

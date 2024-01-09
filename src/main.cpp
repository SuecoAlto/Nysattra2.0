#include <Arduino.h>
#include <WiFi.h>
#include "sensors.h"  // Include the header for sensor functions
#include "secrets.h"
#include <WiFi.h>

#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include "Adafruit_Sensor.h"

#define AWS_IOT_PUBLISH_TOPIC   "Nysattra_pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "Nysattra_sub"

// Your WiFi credentials
const char* ssid = "Tele2_99a515"; 						// WIFI SSID
const char* password = "fjnkdjy2"; 						// WIFI PASSWORD

unsigned long lastAttemptTime = 0;
const unsigned long attemptInterval = 10000;

// Function to check WiFi status and print changes
void checkWiFiStatus() {
  static int lastWiFiStatus = -1;                 // Store the last WiFi status
  if (WiFi.status() != lastWiFiStatus) { // Check if the status has changed
    lastWiFiStatus = WiFi.status(); // Update the last status
    switch (WiFi.status()) {
      case WL_IDLE_STATUS:
        Serial.println("WiFi is idle...\n");
        break;
      case WL_NO_SSID_AVAIL:
        Serial.println("No SSID available. Check WiFi settings.\n");
        break;
      case WL_CONNECT_FAILED:
        Serial.println("Failed to connect. Check password and SSID.\n");
        break;
      case WL_CONNECTION_LOST:
        Serial.println("Connection lost. Trying to reconnect...\n");
        break;
      case WL_DISCONNECTED:
        Serial.println("WiFi disconnected. Attempting to reconnect...\n");
        break;
      default:
        break;
    }
  }
}

void connectToServices() {
  // Anslut till WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to WiFi...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startTime < 10000) {
      delay(500);
      Serial.print(".");
      checkWiFiStatus();
    }
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Failed to connect to WiFi.");
      return;
    }
    Serial.println("Connected to WiFi.");
  }

  // Konfigurera WiFiClientSecure med AWS IoT-certifikat
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Anslut till AWS IoT Core
  Serial.println("Connecting to AWS IoT...");
  client.setServer(AWS_IOT_ENDPOINT, 8883);
  client.setCallback(messageHandler);

  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }

  if (client.connected()) {
    Serial.println("Connected to AWS IoT.");
    client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
  } else {
    Serial.println("AWS IoT Timeout, failed to connect to AWS IoT ");
  }
}


WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);
 

// ---------------------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------- //


void setup() {
  Serial.begin(115200); 								// Start serial communication
  connectToServices(); 										// Call the function to connect to WiFi
  initSensors(); 										// Initialize sensors after starting the serial communication
}



void publishMessage()
{
  StaticJsonDocument<256> doc;          // Create a JSON document
  doc["temperature"] = temperature;
  doc["humidity"] = humidity;
  doc["waterLevel"] = waterLevel;
  doc["soilMoisture"] = soilMoisture; // Fixed: Define the variable "soilMoisture"
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client
 
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}
 
void messageHandler(char* topic, byte* payload, unsigned int length)
{
  Serial.print("incoming: ");
  Serial.println(topic);
 
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["message"];
  Serial.println(message);
}


// New function to print the water level status
void printWaterLevelStatus(int waterLevel) {
    if (waterLevel == WATER_LOW) {
        Serial.println("Low");
    } else if (waterLevel == WATER_MID) {
        Serial.println("Mid");
    } else if (waterLevel == WATER_HIGH) {
        Serial.println("Good");
    } else {
        Serial.println("Water level reading is out of expected range");
    }
}

// New function to print the soil moisture status
void printSoilMoistureStatus(int soilMoisture) {
    if (soilMoisture == MOISTURE_LOW) {
        Serial.println("Low");
    } else if (soilMoisture == MOISTURE_MID) {
        Serial.println("Mid");
    } else if (soilMoisture == MOISTURE_HIGH) {
        Serial.println("High");
    } else {
        Serial.println("Soil moisture reading is out of expected range");
    }
}

// ---------------------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------- //


void loop() {
  
  // Hantera anslutningen till tjänsterna
  unsigned long currentMillis = millis();

  if (WiFi.status() != WL_CONNECTED || !client.connected()) {
    if (currentMillis - lastAttemptTime > attemptInterval) {
      connectToServices();
      lastAttemptTime = currentMillis;
    }
  } else {
    // Hantera MQTT-meddelanden
    client.loop();

    // Läs sensorvärdena här och lagra dem i respektive variabler
    // float temperature, humidity;
    // int waterLevel, soilMoisture;
    // ... (sensorläsningslogik)

    // Publicera sensorvärdena
    publishMessage(); // Se till att de rätta värdena skickas med här

  }

  checkWiFiStatus();

  // Ytterligare logik kan läggas till här vid behov
  
}

// ---------------------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------- //
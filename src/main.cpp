#include <Arduino.h>
#include <WiFi.h>
#include "sensors.h"  // Include the header for sensor functions

// Your WiFi credentials
const char* ssid = "Tele2_99a515"; 						// WIFI SSID
const char* password = "fjnkdjy2"; 						// WIFI PASSWORD

// Function to connect to WiFi
void connectToWiFi() {
  WiFi.mode(WIFI_STA); 									// Set Wi-Fi mode to "Station"
  WiFi.begin(ssid, password);							// Begin connecting to WiFi with provided credentials
  Serial.print("Connecting to WiFi\n"); 					// Print a connecting message
}


// Function to check WiFi status and print changes
void checkWiFiStatus() {
  static int lastWiFiStatus = -1; // Store the last WiFi status
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


void setup() {
  Serial.begin(115200); 								// Start serial communication
  connectToWiFi(); 										// Call the function to connect to WiFi
  initSensors(); 										// Initialize sensors after starting the serial communication
}



void loop() {
  static unsigned long lastAttemptTime = 0; 			// Store the last attempt time
  if (WiFi.status() != WL_CONNECTED) {
    if (millis() - lastAttemptTime > 10000) { 			// Check if 10 seconds have passed
      connectToWiFi(); 									// Attempt to reconnect
      lastAttemptTime = millis(); 						// Update the last attempt time
    }
  } else {
    
    // WiFi is connected, read sensor values here
    float temperature, humidity;
    int waterLevel, soilMoisture;

    if (readTemperature(temperature)) {
        Serial.print("Temperature: ");
        Serial.println(temperature);
    } else {
        Serial.println("Failed to read temperature!");
    }

    if (readHumidity(humidity)) {
        Serial.print("Humidity: ");
        Serial.println(humidity);
    } else {
        Serial.println("Failed to read humidity!");
    }

    if (readWaterLevel(waterLevel)) {
        Serial.print("Water Level: ");
        Serial.println(waterLevel);
    } else {
        Serial.println("Failed to read water level!");
    }

    if (readSoilMoisture(soilMoisture)) {
        Serial.print("Soil Moisture: ");
        Serial.println(soilMoisture);
    } else {
        Serial.println("Failed to read soil moisture! \n");
    }
  
  }

  checkWiFiStatus(); // Check and print the WiFi status
  delay(4000); // Main loop delay
}

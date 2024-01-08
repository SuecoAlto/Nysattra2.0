#include <Arduino.h>

#include "DHT.h"

#define DHTTYPE DHT22   // DHT 22 (AM2302, AM2321)
#define DHTPin 27       // DHT Sensor Pin
#define WaterLevelPin 33 // Water Level Sensor Pin
#define SoilMoisturePin 32 // Soil Moisture Sensor Pin

// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);                

void setup() {
  Serial.begin(115200);
  delay(100);
  dht.begin();
  pinMode(WaterLevelPin, INPUT);       // Initialize the water level pin as an input
  pinMode(SoilMoisturePin, INPUT);     // Initialize the soil moisture pin as an input
}

bool errorOccurred = false;  // Global variable to track if error has occurred

void loop() {
  if (!errorOccurred) {
    float Temperature = dht.readTemperature();
    float Humidity = dht.readHumidity();

    if (isnan(Humidity) || isnan(Temperature)) {
      Serial.println("Failed to read from DHT sensor!");
      errorOccurred = true;  // Set error flag
    } else {
      Serial.print("Temperature: ");
      Serial.print(Temperature);
      Serial.print(" °C, Humidity: ");
      Serial.print(Humidity);
      Serial.println(" %");
    }
  }

  if (errorOccurred) {
    while(true) {
      // Do nothing, effectively stopping the program
    }
  } else {
    delay(2000);  // Normal operation delay
  }
}

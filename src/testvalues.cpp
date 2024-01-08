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



void loop() {

  float Temperature = dht.readTemperature();
  float Humidity = dht.readHumidity();
  int WaterLevel = analogRead(WaterLevelPin);    // Read the water level
  int SoilMoisture = analogRead(SoilMoisturePin); // Read the soil moisture level

if (isnan(Humidity) || isnan(Temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(Temperature);
    Serial.print(" *C ");
    Serial.print("Humidity: ");
    Serial.print(Humidity);
    Serial.print("% ");
  }

  // Assume that a reading of 0 from the analog sensors indicates a failure.
  // Adjust this condition based on the behavior of your specific sensors.
  if (WaterLevel == 0) {
    Serial.println("Failed to read from water level sensor!");
  } else {
    Serial.print("Water Level: ");
    Serial.print(WaterLevel);
    Serial.print(" ");
  }

  if (SoilMoisture == 0) {
    Serial.println("Failed to read from soil moisture sensor!");
  } else {
    Serial.print("Soil Moisture: ");
    Serial.println(SoilMoisture);
  }
  
    delay(2000);  // Normal operation delay
  
}

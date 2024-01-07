#include <Arduino.h>

#include "DHT.h"

#define DHTTYPE DHT22   // DHT 22 (AM2302, AM2321)

// DHT Sensor
uint8_t DHTPin = 27; 

// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);                

void setup() {
  Serial.begin(115200);
  delay(100);
  dht.begin();
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

#include "sensors.h"

// Initialize the DHT sensor
DHT dht(DHTPin, DHT22);

void initSensors() {
    dht.begin();
    pinMode(WaterLevelPin, INPUT);
    pinMode(SoilMoisturePin, INPUT);
}

bool readTemperature(float &temperature) {
    temperature = dht.readTemperature();
    return !isnan(temperature);
}

bool readHumidity(float &humidity) {
    humidity = dht.readHumidity();
    return !isnan(humidity);
}

bool readWaterLevel(int &waterLevel) {
    waterLevel = analogRead(WaterLevelPin);
    return waterLevel > 0; // Assuming 0 is the error value
}

bool readSoilMoisture(int &soilMoisture) {
    soilMoisture = analogRead(SoilMoisturePin);
    return soilMoisture > 0; // Assuming 0 is the error value
}

#include "sensors.h"

// Initialize the DHT sensor
DHT dht(DHTPin, DHT22);

// Define water level categories
const int LOW = 1;
const int MID = 2;
const int HIGH = 3;


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
    if (waterLevel == 0) {
        // Error value, sensor not reading correctly
        return false;
    } else if (waterLevel > 0 && waterLevel <= 300) {
        // LOW water level
        waterLevel = LOW;
    } else if (waterLevel > 300 && waterLevel <= 700) {
        // MID water level
        waterLevel = MID;
    } else if (waterLevel > 700) {
        // HIGH water level
        waterLevel = HIGH;
    }
    return true;
}

bool readSoilMoisture(int &soilMoisture) {
    soilMoisture = analogRead(SoilMoisturePin);
    return soilMoisture > 0; // Assuming 0 is the error value
}

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
    if (waterLevel == 0) {
        // Error value, sensor not reading correctly
        return false;
    } else if (waterLevel > 0 && waterLevel <= 300) {
        // LOW water level
        waterLevel = WATER_LOW;
    } else if (waterLevel > 300 && waterLevel <= 700) {
        // MID water level
        waterLevel = WATER_MID;
    } else if (waterLevel > 700) {
        // HIGH water level
        waterLevel = WATER_HIGH;
    }
    return true;
}

bool readSoilMoisture(int &soilMoisture) {
    soilMoisture = analogRead(SoilMoisturePin);
        if (soilMoisture == 0) {
        // Error value, sensor not reading correctly
        return false;
    } else if (soilMoisture > 0 && soilMoisture <= 300) {
        // LOW moisture level
        soilMoisture = MOISTURE_LOW;
    } else if (soilMoisture > 300 && soilMoisture <= 700) {
        // MID moisture level
        soilMoisture = MOISTURE_MID;
    } else if (soilMoisture > 700) {
        // HIGH moisture level
        soilMoisture = MOISTURE_HIGH;
    }
    return true;
}

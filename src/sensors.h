#ifndef SENSORS_H
#define SENSORS_H

#include "DHT.h"

// Sensor pins
const int DHTPin = 27;
const int WaterLevelPin = 33;
const int SoilMoisturePin = 32;

// Define water level categories
const int WATER_LOW = 1;
const int WATER_MID = 2;
const int WATER_HIGH = 3;

// Define moisture level categories
const int MOISTURE_LOW = 1;
const int MOISTURE_MID = 2;
const int MOISTURE_HIGH = 3;

// Initialization function
void initSensors();

// Sensor read functions with error handling
bool readTemperature(float &temperature);
bool readHumidity(float &humidity);
bool readWaterLevel(int &waterLevel);
bool readSoilMoisture(int &soilMoisture);

#endif // SENSORS_H

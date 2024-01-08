#ifndef SENSORS_H
#define SENSORS_H

#include "DHT.h"

// Sensor pins
const int DHTPin = 27;
const int WaterLevelPin = 33;
const int SoilMoisturePin = 32;

// Initialization function
void initSensors();

// Sensor read functions with error handling
bool readTemperature(float &temperature);
bool readHumidity(float &humidity);
bool readWaterLevel(int &waterLevel);
bool readSoilMoisture(int &soilMoisture);

#endif // SENSORS_H

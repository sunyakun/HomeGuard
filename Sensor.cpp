#include <Arduino.h>
#include "Sensor.h"
#include "setting.h"
Sensor::Sensor(String type, int pin){
	this->type = type;
	this->pin = pin;
	getUUID(UUID);
}

void Sensor::getUUID(String id){
	sensorId = id + type;
}
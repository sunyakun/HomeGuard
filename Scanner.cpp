#include <string.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include "Sensor.h"
#include "Scanner.h"
#include "func.h"
#include "setting.h"

char* buffer = new char[SIZE];
Scanner::Scanner(){
	count = 0;
	head = NULL;
}
String Scanner::packSensorData(){
	node* p = head;
	StaticJsonBuffer<SIZE> jsonBuffer;
	JsonObject& json = jsonBuffer.createObject();
	json["id"] = UUID;
	json["time"] = millis();
	JsonArray& jsonArray = json.createNestedArray("sensor");
	while(p!=NULL){
		JsonObject& sensorJson = jsonBuffer.createObject();
		sensorJson["type"] = p->sensor.type;
		sensorJson["pin"] = p->sensor.pin;
		sensorJson["value"] = analogRead(p->sensor.pin);
		sensorJson["sensorId"] = p->sensor.sensorId;
		jsonArray.add(sensorJson);
		p = p->next;
	}
	json.printTo(buffer, SIZE);
	Serial.println("[DEBUG]:sensor data collect is complete");
	return pack2http(String(buffer));
}

void Scanner::registerSensor(Sensor sensor){
	if(head == NULL){
		head = new node();
		head->sensor = sensor;
		return;
	}
	else if(head->sensor.pin == sensor.pin){
		head->sensor = sensor;
		return ;
	}
	node* pos = head;
	while(pos->next != NULL && pos->next->sensor.pin != sensor.pin){
		pos = pos->next;
	}
	pos->next = new node();
	pos = pos->next;
	pos->sensor = sensor;
}

#ifndef __SCANNER__
#define __SCANNER__

#include "Sensor.h"
class Scanner{
public:
	Scanner();
	String packSensorData();
	void registerSensor(Sensor);
private:
	struct node{
		Sensor sensor;
		node* next = NULL;
	};
	int count;
	node* head;
};
#endif
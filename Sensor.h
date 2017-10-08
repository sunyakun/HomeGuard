#ifndef __SENSOR__
#define __SENSOR__

#include <string.h>
class Sensor{
public:
	Sensor(){}
	Sensor(String type, int pin);
	String type;
	String sensorId;
	int pin;
private:
	void getUUID(String);
};

#endif
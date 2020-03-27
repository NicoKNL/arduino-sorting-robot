#ifndef SENSOR_HH
#define SENSOR_HH
#include "ISensor.hh"
class Sensor : public skel::Sensor {
	int mPin = -1;
	void sensor_initialise(int pin);

public:
	Sensor(const dzn::locator& loc);
	
	void detect();
};

#endif

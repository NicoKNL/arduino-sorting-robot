#ifndef SENSOR_HH
#define SENSOR_HH
#include "ISensor.hh"
class Sensor : public skel::Sensor {
	void sensor_initialise();
//	void detected();

public:
	Sensor(const dzn::locator& loc);
};
#endif

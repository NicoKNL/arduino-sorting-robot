#include <dzn/runtime.hh>
#include <dzn/locator.hh>
#include "internal_belt.hh"


#ifndef SENSOR_HH
#define SENSOR_HH
class Sensor : public skel::SensorEnd {
	void initialise();
	void detected();

public:
	Sensor(const dzn::locator& loc);
};
#endif

#include <dzn/runtime.hh>
#include <dzn/locator.hh>
#include "Grabber.hh"


#ifndef SENSOR_HH
#define SENSOR_HH
class Sensor : public skel::Sensor {
	void initialise();
	void detected();

public:
	Sensor(const dzn::locator& loc);
};
#endif

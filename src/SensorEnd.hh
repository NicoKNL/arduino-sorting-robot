#include <dzn/runtime.hh>
#include <dzn/locator.hh>
#include "internal_belt.hh"


#ifndef SENSOREND_HH
#define SENSOREND_HH
class SensorEnd : public skel::SensorEnd {
	void initialise();
	void detected();

public:
	SensorEnd(const dzn::locator& loc);
};
#endif

#ifndef SENSOREND_HH
#define SENSOREND_HH
#include "internal_belt.hh"
class SensorEnd : public skel::SensorEnd {
	void sensorEnd_initialise();
//	void detected();

public:
	SensorEnd(const dzn::locator& loc);
};
#endif

#ifndef ACTUATOR_HH
#define ACTUATOR_HH
#include "IActuator.hh"
class Actuator : public skel::Actuator {
	int mPin = -1;
	void actuator_initialise(int pin);

public:
	Actuator(const dzn::locator& loc);

	void actuator_extend();
	void actuator_withdraw();
};

#endif

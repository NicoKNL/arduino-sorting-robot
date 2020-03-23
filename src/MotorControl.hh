#include <dzn/runtime.hh>
#include <dzn/locator.hh>
#include "internal_belt.hh"


#ifndef MOTORCONTROL_HH
#define MOTORCONTROL_HH
class MotorControl : public skel::MotorControl {
	void initialise();
	void goForward();
	void goBackward();
	void stop();

public:
	MotorControl(const dzn::locator& loc);
};
#endif
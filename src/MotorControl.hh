#ifndef MOTORCONTROL_HH
#define MOTORCONTROL_HH
#include "IMotorControl.hh"
class MotorControl : public skel::MotorControl {
	void motorControl_initialise();
	void motorControl_goForward();
	void motorControl_goBackward();
	void motorControl_stop();

public:
	MotorControl(const dzn::locator& loc);
};
#endif

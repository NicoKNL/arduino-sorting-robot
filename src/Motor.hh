#ifndef MOTOR_HH
#define MOTOR_HH
#include "IMotor.hh"
class Motor : public skel::Motor {
	int mPin = -1;
	bool mState = false;
	void motor_initialise(int pin);

public:
	Motor(const dzn::locator& loc);

	void motor_turnOn();
	void motor_turnOff();
};

#endif

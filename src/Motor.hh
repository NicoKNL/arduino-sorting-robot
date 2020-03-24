#ifndef MOTOR_HH
#define MOTOR_HH
#include "Grabber.hh"
class Motor : public skel::Motor {
	void motor_next();
	void motor_reset();
//	void finished();
//	void error();

public:
	Motor(const dzn::locator& loc);
};
#endif

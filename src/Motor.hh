#include <dzn/runtime.hh>
#include <dzn/locator.hh>
#include "Grabber.hh"

#ifndef MOTOR_HH
#define MOTOR_HH
class Motor : public skel::Motor {
	void next();
	void reset();
	void finished();
	void error();

public:
	Motor(const dzn::locator& loc);
};
#endif

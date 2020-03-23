#include <dzn/runtime.hh>
#include <dzn/locator.hh>


#ifndef MOTOR_HH
#define MOTOR_HH
class Motor : public skel::SensorEnd {
	void next();
	void reset();
	void finished();
	void error();

public:
	Motor(const dzn::locator& loc);
};
#endif

#ifndef LED_HH
#define LED_HH
#include "ILed.hh"
class Led : public skel::Led {
	void iLed_turnOff();
	void iLed_turnOn();

	public:
		Led(const dzn::locator& loc);
};
#endif

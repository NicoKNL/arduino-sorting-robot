#ifndef LED_HH
#define LED_HH
#include "ILed.hh"
class Led : public skel::Led {
	int mPin = -1;
	void led_turnOn();
	void led_turnOff();

	public:
		Led(const dzn::locator& loc);
};
#endif

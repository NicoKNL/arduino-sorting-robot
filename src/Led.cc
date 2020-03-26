#include "Led.hh"
// #include <wiringPi.h>

Led::Led(const dzn::locator& loc) : skel::Led(loc) {

}

int PIN = 5;
void Led::iLed_turnOff() {
	//digitalWrite(PIN, LOW);
}
void Led::iLed_turnOn(){
	//	digitalWrite(PIN, HIGH);
}

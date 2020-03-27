#include "Led.hh"
// #include <wiringPi.h>
// #include <iostream>

Led::Led(const dzn::locator& loc) : skel::Led(loc) {

}

void Led::led_turnOn() {
  // std::cout << "Ledje gaat aan op: " << mPin << '\n';
	//digitalWrite(PIN, LOW);
}
void Led::led_turnOff(){
  // std::cout << "Ledje gaat uit op: " << mPin << '\n';
	//	digitalWrite(PIN, HIGH);
}

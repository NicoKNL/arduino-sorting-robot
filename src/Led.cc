#include "Led.hh"
#include <wiringPi.h>
#include <iostream>

Led::Led(const dzn::locator& loc) : skel::Led(loc) {

}

void Led::led_initialise (int pin) {
  mPin = pin;
}

void Led::led_turnOn() {
  std::cout << "Ledje gaat aan op: " << mPin << '\n';
	digitalWrite(mPin, 1);
}
void Led::led_turnOff(){
  std::cout << "Ledje gaat uit op: " << mPin << '\n';
	digitalWrite(mPin, 0);
}

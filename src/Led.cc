#include "Led.hh"
#include <wiringPi.h>
#include <iostream>

Led::Led(const dzn::locator& loc) : skel::Led(loc) {

}

void Led::led_initialise (int pin) {
  std::cout << "[Led] Initialising on pin: " << mPin << ".\n";
  mPin = pin;
}

void Led::led_turnOn() {
  std::cout << "[Led] gaat aan op: " << mPin << '\n';
	digitalWrite(mPin, HIGH);
}
void Led::led_turnOff(){
  std::cout << "[Led] gaat uit op: " << mPin << '\n';
	digitalWrite(mPin, LOW);
}

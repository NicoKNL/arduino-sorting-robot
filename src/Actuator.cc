#include "Actuator.hh"
#include <iostream>
#include "config.hh"
#include <wiringPi.h>

Actuator::Actuator(const dzn::locator& loc) : skel::Actuator(loc) {

}

void Actuator::actuator_initialise(int pin) {
	mPin = pin;
	std::cout << "[Actuator] Initialising on pin: " << mPin << ".\n";
}

void Actuator::actuator_extend() {
	std::cout << "[Actuator] Extending!\n";
	if (!Debug::DEBUG) {
		digitalWrite(mPin, HIGH);
	}
}

void Actuator::actuator_withdraw() {
	std::cout << "[Actuator] Withdrawing!\n";
	if (!Debug::DEBUG) {
		digitalWrite(mPin, LOW);
	}
}

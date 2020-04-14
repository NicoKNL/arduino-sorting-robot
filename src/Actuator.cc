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
	if (mState != true) {
		std::cout << "[Actuator] Extending!\n";
	}
	if (!Config::DEBUG) {
		digitalWrite(mPin, HIGH);
	}
	mState = true;
}

void Actuator::actuator_withdraw() {
	if (mState != false) {
		std::cout << "[Actuator] Withdrawing!\n";
	}
	if (!Config::DEBUG) {
		digitalWrite(mPin, LOW);
	}
	mState = false;
}

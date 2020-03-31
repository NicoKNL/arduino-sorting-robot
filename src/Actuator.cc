#include "Actuator.hh"
#include <iostream>

Actuator::Actuator(const dzn::locator& loc) : skel::Actuator(loc) {

}

void Actuator::actuator_initialise(int pin) {
	mPin = pin;
	std::cout << "[Actuator] Initialising on pin: " << mPin << ".\n";
}

void Actuator::actuator_extend() {
	// digitalWrite(mPin, HIGH);
	std::cout << "[Actuator] Extending!\n";
}

void Actuator::actuator_withdraw() {
	// digitalWrite(mPin, LOW);
	std::cout << "[Actuator] Withdrawing!\n";
}

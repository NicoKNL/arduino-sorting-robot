#include "Motor.hh"
#include <iostream>

Motor::Motor(const dzn::locator& loc) : skel::Motor(loc) {

}

void Motor::motor_initialise(int pin) {
	mPin = pin;
	std::cout << "[Motor] Initialising on pin: " << mPin << ".\n";
}

void Motor::motor_turnOn() {
	std::cout << "[Motor] Turning on!\n";
}

void Motor::motor_turnOff() {
	std::cout << "[Motor] Turning off!\n";
}

#include "Motor.hh"
#include <iostream>
#include "config.hh"
#include <wiringPi.h>

Motor::Motor(const dzn::locator& loc) : skel::Motor(loc) {

}

void Motor::motor_initialise(int pin) {
	mPin = pin;
	std::cout << "[Motor] Initialising on pin: " << mPin << ".\n";
}

void Motor::motor_turnOn() {
	std::cout << "[Motor] Turning on!\n";
	if (!Debug::DEBUG) {
		digitalWrite(mPin, HIGH);
	}
}

void Motor::motor_turnOff() {
	std::cout << "[Motor] Turning off!\n";
	if (!Debug::DEBUG) {
		digitalWrite(mPin, LOW);
	}
}

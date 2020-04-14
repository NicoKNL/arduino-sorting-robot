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
	if (mState != true) {
		std::cout << "[Motor] Turning on!\n";
	}

	if (!Config::DEBUG) {
		digitalWrite(mPin, HIGH);
	}
	mState = true;
}

void Motor::motor_turnOff() {
	if (mState != false) {
		std::cout << "[Motor] Turning off!\n";
	}

	if (!Config::DEBUG) {
		digitalWrite(mPin, LOW);
	}
	mState = false;
}

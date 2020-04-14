#include "Sensor.hh"
#include <iostream>
#include "config.hh"
#include <wiringPi.h>

Sensor::Sensor(const dzn::locator& loc) : skel::Sensor(loc) {

}

void Sensor::sensor_initialise(int pin) {
	mPin = pin;
	std::cout << "[Sensor] Initialising on pin: " << mPin << ".\n";
}

void Sensor::detect() {
	int state;

	if (Config::DEBUG) {
		std::cout << "[Sensor] detecting!\n";
		std::cin >> state;
	} else {
		state = digitalRead(mPin);
	}

	if (state == 0) {
		if (Config::DEBUG) {
			std::cout << "[Sensor] Nothing detected...\n";
		}
		mState = false;
	} else {
		if (mState != true) {
			std::cout << "[Sensor] Setting to high!\n";
		}
		sensor.out.high();
		mState = true;
	}
}

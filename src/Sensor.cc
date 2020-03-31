#include "Sensor.hh"
#include <iostream>

Sensor::Sensor(const dzn::locator& loc) : skel::Sensor(loc) {

}

void Sensor::sensor_initialise(int pin) {
	mPin = pin;
	std::cout << "[Sensor] Initialising on pin: " << mPin << ".\n";
}

void Sensor::detect() {
	std::cout << "[Sensor] detecting!\n";
	int state;
	std::cin >> state;
	// state = digitalRead(mPin);
	if (state == 0) {
		std::cout << "[Sensor] Nothing detected...\n";
	} else {
		std::cout << "[Sensor] Setting to high!\n";
		sensor.out.high();
	}
}

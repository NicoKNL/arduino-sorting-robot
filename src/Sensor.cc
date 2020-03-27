#include "Sensor.hh"
#include <iostream>

Sensor::Sensor(const dzn::locator& loc) : skel::Sensor(loc) {

}

void Sensor::sensor_initialise(int pin) {
	// mPin = pin;
	// std::cout << "Grabber.Sensor: Initialising on pin: " << mPin << ".\n";
}

void Sensor::detect() {
	std::cout << "detected!\n";
	int state;
	std::cin >> state;
	if (state == 0) {
		std::cout << "Setting to low!\n";
		sensor.out.low();
	} else {
		std::cout << "Setting to high!\n";
		sensor.out.high();
	}
}
//void Sensor::detected() {
//	std::cout << "Grabber.Sensor: Disk detected." << std::endl;
//}

#include <dzn/runtime.hh>
#include <dzn/locator.hh>
#include "Grabber.hh"
#include "Sensor.hh"

void Sensor::initialise() {
	std::cout << "Sensor: Initialising." << std::endl;
}
void Sensor::detected() {
	std::cout << "Sensor: Disk detected." << std::endl;
}
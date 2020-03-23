#include <dzn/runtime.hh>
#include <dzn/locator.hh>
#include "internal_belt.hh"
#include "SensorEnd.hh"

void SensorEnd::initialise() {
	std::cout << "Belt.EndSensor: Initialising." << std::endl;
}
void SensorEnd::detected() {
	std::cout << "Belt.EndSensor: Disk detected." << std::endl;
}
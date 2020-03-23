#include <dzn/runtime.hh>
#include <dzn/locator.hh>
#include "internal_belt.hh"
#include "PresSensorBlackStack.hh"

void PresSensorBlackStack::initialise() {
	std::cout << "Belt.BlackSensor: Initialising." << std::endl;
}
void PresSensorBlackStack::detected() {
	std::cout << "Belt.BlackSensor: Disk detected." << std::endl;
}
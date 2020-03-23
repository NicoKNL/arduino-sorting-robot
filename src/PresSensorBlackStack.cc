#include <dzn/runtime.hh>
#include <dzn/locator.hh>
#include "internal_belt.hh"
#include "PresSensorBlackStack.hh"

void PresSensorBlackStack::initialise() {
	std::cout << "BlackSensor: Initialising." << std::endl;
}
void PresSensorBlackStack::detected() {
	std::cout << "BlackSensor: Disk detected." << std::endl;
}
#include <dzn/runtime.hh>
#include <dzn/locator.hh>
#include "internal_belt.hh"
#include "PresSensorWhiteStack.hh"

void PresSensorWhiteStack::initialise() {
	std::cout << "WhiteSensor: Initialising." << std::endl;
}
void PresSensorWhiteStack::detected() {
	std::cout << "WhiteSensor: Disk detected." << std::endl;
}
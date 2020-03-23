#include <dzn/runtime.hh>
#include <dzn/locator.hh>
#include "internal_belt.hh"
#include "PresSensorWhiteStack.hh"

void PresSensorWhiteStack::initialise() {
	std::cout << "Belt.WhiteSensor: Initialising." << std::endl;
}
void PresSensorWhiteStack::detected() {
	std::cout << "Belt.WhiteSensor: Disk detected." << std::endl;
}
#include <dzn/runtime.hh>
#include <dzn/locator.hh>
#include "internal_belt.hh"
#include "MotorControl.hh"

void MotorControl::initialise() {
	std::cout << "Motor: Initialising." << std::endl;
}
void MotorControl::goForward() {
	std::cout << "Motor: Moving belt forwards." << std::endl;
}
void MotorControl::goBackward() {
	std::cout << "Motor: Moving belt backwards." << std::endl;
}
void MotorControl::stop() {
	std::cout << "Motor: Stopping the belt." << std::endl;
}
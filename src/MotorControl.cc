#include <dzn/runtime.hh>
#include <dzn/locator.hh>
#include "internal_belt.hh"
#include "MotorControl.hh"

void MotorControl::initialise() {
	std::cout << "Belt.MotorControl: Initialising." << std::endl;
}
void MotorControl::goForward() {
	std::cout << "Belt.MotorControl: Moving belt forwards." << std::endl;
}
void MotorControl::goBackward() {
	std::cout << "Belt.MotorControl: Moving belt backwards." << std::endl;
}
void MotorControl::stop() {
	std::cout << "Belt.MotorControl: Stopping the belt." << std::endl;
}
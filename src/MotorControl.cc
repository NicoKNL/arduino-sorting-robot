#include "MotorControl.hh"

MotorControl::MotorControl(const dzn::locator& loc) : skel::MotorControl(loc) {
}

void MotorControl::motorControl_initialise() {
	std::cout << "Belt.MotorControl: Initialising." << std::endl;
}
void MotorControl::motorControl_goForward() {
	std::cout << "Belt.MotorControl: Moving belt forwards." << std::endl;
}
void MotorControl::motorControl_goBackward() {
	std::cout << "Belt.MotorControl: Moving belt backwards." << std::endl;
}
void MotorControl::motorControl_stop() {
	std::cout << "Belt.MotorControl: Stopping the belt." << std::endl;
}

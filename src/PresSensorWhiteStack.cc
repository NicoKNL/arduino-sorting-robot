#include "PresSensorWhiteStack.hh"

PresSensorWhiteStack::PresSensorWhiteStack(const dzn::locator& loc) : skel::PresSensorWhiteStack(loc) {

}

void PresSensorWhiteStack::sensorWhite_initialise() {
	std::cout << "Belt.WhiteSensor: Initialising." << std::endl;
}
//void PresSensorWhiteStack::detected() {
//	std::cout << "Belt.WhiteSensor: Disk detected." << std::endl;
//}

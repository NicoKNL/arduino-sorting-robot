#include "PresSensorBlackStack.hh"

PresSensorBlackStack::PresSensorBlackStack(const dzn::locator& loc) : skel::PresSensorBlackStack(loc) {

}

void PresSensorBlackStack::sensorBlack_initialise() {
	std::cout << "Belt.BlackSensor: Initialising." << std::endl;
}
//void PresSensorBlackStack::detected() {
//	std::cout << "Belt.BlackSensor: Disk detected." << std::endl;
//}

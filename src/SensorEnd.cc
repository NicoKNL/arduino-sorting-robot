#include "SensorEnd.hh"

SensorEnd::SensorEnd(const dzn::locator& loc) : skel::SensorEnd(loc) {

}

void SensorEnd::sensorEnd_initialise() {
	std::cout << "Belt.EndSensor: Initialising." << std::endl;
}
//void SensorEnd::detected() {
//	std::cout << "Belt.EndSensor: Disk detected." << std::endl;
//}

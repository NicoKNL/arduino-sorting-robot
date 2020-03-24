#include "Sensor.hh"

Sensor::Sensor(const dzn::locator& loc) : skel::Sensor(loc) {

}

void Sensor::sensor_initialise() {
	std::cout << "Grabber.Sensor: Initialising." << std::endl;
}
//void Sensor::detected() {
//	std::cout << "Grabber.Sensor: Disk detected." << std::endl;
//}

#include "Motor.hh"

Motor::Motor(const dzn::locator& loc) : skel::Motor(loc) {

}

void Motor::motor_next() {
	std::cout << "Grabber.Motor: Grabbing next disk." << std::endl;
}
void Motor::motor_reset() {
	std::cout << "Grabber.Motor: Resetting to initial position." << std::endl;
}
//void Motor::finished() {
//	std::cout << "Grabber.Motor: Finished grabbing disk." << std::endl;
//}
//void Motor::error() {
//	std::cout << "Grabber.Motor: Grabbing disk failed." << std::endl;
//}

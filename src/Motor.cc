#include <dzn/runtime.hh>
#include <dzn/locator.hh>
#include "Grabber.hh"
#include "Motor.hh"

void Motor::next() {
	std::cout << "Grabber.Motor: Grabbing next disk." << std::endl;
}
void Motor::reset() {
	std::cout << "Grabber.Motor: Resetting to initial position." << std::endl;
}
void Motor::finished() {
	std::cout << "Grabber.Motor: Finished grabbing disk." << std::endl;
}
void Motor::error() {
	std::cout << "Grabber.Motor: Grabbing disk failed." << std::endl;
}
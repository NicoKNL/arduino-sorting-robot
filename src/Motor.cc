#include <dzn/runtime.hh>
#include <dzn/locator.hh>
#include "Grabber.hh"
#include "Motor.hh"

void Motor::next() {
	std::cout << "Motor: Grabbing next disk." << std::endl;
}
void Motor::reset() {
	std::cout << "Motor: Resetting to initial position." << std::endl;
}
void Motor::finished() {
	std::cout << "Motor: Finished grabbing disk." << std::endl;
}
void Motor::error() {
	std::cout << "Motor: Grabbing disk failed." << std::endl;
}
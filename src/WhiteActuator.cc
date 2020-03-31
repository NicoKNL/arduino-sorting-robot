#include "WhiteActuator.hh"
#include <iostream>

WhiteActuator::WhiteActuator(const dzn::locator& loc) : skel::WhiteActuator(loc) {

}

void WhiteActuator::whiteActuator_extend() {
	std::cout << "WhiteActuator: extending..\n";
}

void WhiteActuator::whiteActuator_withdraw() {
	std::cout << "WhiteActuator: withdrawing..\n";
}

#include "BlackActuator.hh"
#include <iostream>

BlackActuator::BlackActuator(const dzn::locator& loc) : skel::BlackActuator(loc) {

}

void BlackActuator::blackActuator_extend() {
	std::cout << "BlackActuator: extending..\n";
}

void BlackActuator::blackActuator_withdraw() {
	std::cout << "BlackActuator: withdrawing..\n";
}

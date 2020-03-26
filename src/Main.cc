#include <dzn/runtime.hh>
#include <dzn/locator.hh>

#include "SortingRobotComp.hh"
#include <iostream>

int main(int argc, char* argv[]) {
	dzn::locator locator;
	dzn::runtime runtime;
	locator.set(runtime);


	// Controller controller(locator);
	SortingRobot sorting_robot(locator);

	// Missing bindings
	sorting_robot.controller.reporter.in.report = []{ std::cout << "report\n"; };
	sorting_robot.controller.reporter.in.turnOff = []{ std::cout << "turnOff\n"; };
	sorting_robot.controller.reporter.in.setWaiting = []{ std::cout << "setWaiting\n"; };
	sorting_robot.controller.reporter.in.setReceived = []{ std::cout << "setReceived\n"; };
	sorting_robot.controller.reporter.in.setDispensing = []{ std::cout << "setDispensing\n"; };

	sorting_robot.controller.belt.in.initialise = []{ std::cout << "belt initialise\n"; };
	sorting_robot.controller.belt.in.toStackBlack = []{ std::cout << "to stack black\n"; };
	sorting_robot.controller.belt.in.toStackWhite = []{ std::cout << "to stack white\n"; };
	sorting_robot.controller.belt.in.toEnd = []{ std::cout << "to end\n"; };



	sorting_robot.check_bindings();

	std::cout<< "Pre init\n";

	// while (true) {
		sorting_robot.i.in.init();
		// controller.in.init();
	std::cout<< "Post init\n";

	// }
}

#include <dzn/runtime.hh>
#include <dzn/locator.hh>

#include "SortingRobot.hh"
#include <iostream>
#include "wiringPi.h"

int main(int argc, char* argv[]) {
	dzn::locator locator;
	dzn::runtime runtime;
	locator.set(runtime);

	SortingRobotSystem robbie_de_robot(locator);

	robbie_de_robot.check_bindings();

	//Start the system! Just like Sten! <3
	robbie_de_robot.master.in.start();

	while (true) {
		std::cout << "step\n";
		robbie_de_robot.sensor.detect(); // Input sensor detection
		delay(500); // 500 ms
	}
	return 0;
}

#include <dzn/runtime.hh>
#include <dzn/locator.hh>

#include "SortingRobot.hh"

int main(int argc, char* argv[]) {
	dzn::locator loc;
	dzn::runtime rt;
	loc.set(rt);

	Controller() controller(loc);
	controller.check_bindings();

	while (true ) {
		controller.i.init();
	}
}

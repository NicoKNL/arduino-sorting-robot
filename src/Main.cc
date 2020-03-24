#include <dzn/runtime.hh>
#include <dzn/locator.hh>

#include "SortingRobot.hh"

int main(int argc, char* argv[]) {
	dzn::locator locator;
	dzn::runtime runtime;
	locator.set(runtime);

	Controller controller(locator);
	controller.check_bindings();

	//while (true ) {
	//	controller.in.init();
	//}
}

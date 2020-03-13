#include <dzn/runtime.hh>
#include <dzn/locator.hh>

#include "Reporter.hh"

int main(int argc, char* argv[]) {
	dzn::locator loc;
	dzn::runtime rt;
	loc.set(rt);

	Reporter r(loc);
	r.check_bindings()

	while (true ) {
		r.iReporter.in.report();
	}
}

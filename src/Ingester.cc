#include "Ingester.hh"
#include <iostream>

Ingester::Ingester(const dzn::locator& loc) : skel::Ingester(loc) {

}

void Ingester::ingest_startIngest() {
	std::cout << "Ingester: Starting..\n";

	// temporary delay and activation of finished() since ingester dezyne is not complete yet
	std::cout << "Ingester: Any button to continue..\n";
	int temp;
	std::cin >> temp;

	ingest.out.finished();
}

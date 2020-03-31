#ifndef INGESTER_HH
#define INGESTER_HH
#include "IIngest.hh"

class Ingester : public skel::Ingester {
	Ingester(const dzn::locator& loc);


	void ingest_startIngest();
};

#endif

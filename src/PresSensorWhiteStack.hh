#ifndef PRESSENSORWHITESTACK_HH
#define PRESSENSORWHITESTACK_HH
#include "internal_belt.hh"
class PresSensorWhiteStack : public skel::PresSensorWhiteStack {
	void sensorWhite_initialise();
	void detected();

public:
	PresSensorWhiteStack(const dzn::locator& loc);
};
#endif

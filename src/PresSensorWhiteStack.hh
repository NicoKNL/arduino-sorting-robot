#ifndef PRESSENSORWHITESTACK_HH
#define PRESSENSORWHITESTACK_HH
#include "IInternalBeltControl.hh"
class PresSensorWhiteStack : public skel::PresSensorWhiteStack {
	void sensorWhite_initialise();
	void detected();

public:
	PresSensorWhiteStack(const dzn::locator& loc);
};
#endif

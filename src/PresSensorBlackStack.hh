#ifndef PRESSENSORBLACKSTACK_HH
#define PRESSENSORBLACKSTACK_HH
#include "IInternalBeltControl.hh"
class PresSensorBlackStack : public skel::PresSensorBlackStack {
	void sensorBlack_initialise();
//	void detected();

public:
	PresSensorBlackStack(const dzn::locator& loc);
};
#endif

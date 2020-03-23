#include <dzn/runtime.hh>
#include <dzn/locator.hh>
#include "internal_belt.hh"


#ifndef PRESSENSORBLACKSTACK_HH
#define PRESSENSORBLACKSTACK_HH
class PresSensorBlackStack : public skel::PresSensorBlackStack {
	void initialise();
	void detected();

public:
	PresSensorBlackStack(const dzn::locator& loc);
};
#endif

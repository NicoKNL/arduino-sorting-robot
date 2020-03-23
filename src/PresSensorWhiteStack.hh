#include <dzn/runtime.hh>
#include <dzn/locator.hh>
#include "internal_belt.hh"


#ifndef PRESSENSORWHITESTACK_HH
#define PRESSENSORWHITESTACK_HH
class PresSensorWhiteStack : public skel::PresSensorWhiteStack {
	void initialise();
	void detected();

public:
	PresSensorWhiteStack(const dzn::locator& loc);
};
#endif

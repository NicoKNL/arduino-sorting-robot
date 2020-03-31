#ifndef COLOURSENSOR_HH
#define COLOURSENSOR_HH
#include "IColourSensor.hh"
class ColourSensor : public skel::ColourSensor {
	int mPinA = -1;
	int mPinB = -2;
	void colourSensor_initialise(int pinA, int pinB);

public:
	ColourSensor(const dzn::locator& loc);

	void detect();
};

#endif

#include "ColourSensor.hh"
#include <iostream>
#include "config.hh"
#include <wiringPi.h>

ColourSensor::ColourSensor(const dzn::locator& loc) : skel::ColourSensor(loc) {

}

void ColourSensor::colourSensor_initialise(int pinA, int pinB) {
	mPinA = pinA;
	mPinB = pinB;
	std::cout << "[ColourSensor] Initialising on pins: " << mPinA << ", " << mPinB << ".\n";
}

void ColourSensor::detect() {

	// 00 - nothing
	// 01 - white disk
	// 10 - black disk
	// 11 - other

	int stateA;
	int stateB;

	if (Config::DEBUG) {
		std::cout << "[ColourSensor] detecting...\n";
		std::cin >> stateA >> stateB;
	} else {
		stateA = digitalRead(mPinA);
		stateB = digitalRead(mPinB);
	}

	int state = stateA;
	state += 2 * stateB;

	// NOTE: Exact states unkown, ask Olivier for definition
	if (state == 1) {
		std::cout << "[ColourSensor] white disk detected!\n";
		colourSensor.out.detectedWhite();
	}
	else if (state == 2) {
		std::cout << "[ColourSensor] black disk detected!\n";
		colourSensor.out.detectedBlack();
	}
	else if (state == 3) {
		std::cout << "[ColourSensor] unknown object detected!\n";
		colourSensor.out.detectedUnknown();
	}
	else {
		if (Config::DEBUG) {
			std::cout << "[ColourSensor] nothing detected.\n";
		}
	}
}

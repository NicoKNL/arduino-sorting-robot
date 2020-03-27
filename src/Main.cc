#include <dzn/runtime.hh>
#include <dzn/locator.hh>

#include "SortingRobot.hh"
#include <iostream>
#include "wiringPi.h"

/*******************************************************************************
 * PIN LAYOUT
 ******************************************************************************/
// General outputs
#define MOVE_BELT_OUT_PIN 7
#define MAIN_PUSHER_OUT_PIN 0
#define WHITE_PUSHER_OUT_PIN 2
#define BLACK_PUSHER_OUT_PIN 3

// General inputs
#define MAIN_PRESENCE_IN_PIN 1
#define MAIN_PUSHER_ENDSTOP_IN_PIN 6
#define WHITE_SENSOR_IN_PIN 26
#define BLACK_SENSOR_IN_PIN 27

// Pins which encode information via combinations
#define STATUS_2_OUT_PIN 21
#define STATUS_1_OUT_PIN 22
#define STATUS_0_OUT_PIN 23

#define COLOR_SENSOR_0_IN_PIN 4
#define COLOR_SENSOR_1_IN_PIN 5

/*******************************************************************************
 * Initial setup wiringPi
 ******************************************************************************/
wiringPiSetup(); // Regular wiringPi pin mode setup

// OUTPUT PINS
pinMode(MOVE_BELT_OUT_PIN, OUTPUT);
pinMode(MAIN_PUSHER_OUT_PIN, OUTPUT);
pinMode(WHITE_PUSHER_OUT_PIN, OUTPUT);
pinMode(BLACK_PUSHER_OUT_PIN, OUTPUT);
pinMode(STATUS_2_OUT_PIN, OUTPUT);
pinMode(STATUS_1_OUT_PIN, OUTPUT);
pinMode(STATUS_0_OUT_PIN, OUTPUT);

// INPUT PINS
pinMode(MAIN_PRESENCE_IN_PIN, INPUT);
pinMode(MAIN_PUSHER_ENDSTOP_IN_PIN, INPUT);
pinMode(WHITE_SENSOR_IN_PIN, INPUT);
pinMode(BLACK_SENSOR_IN_PIN, INPUT);
pinMode(COLOR_SENSOR_0_IN_PIN, INPUT);
pinMode(COLOR_SENSOR_1_IN_PIN, INPUT);


/*******************************************************************************
 * ENTRY POINT CODE
 ******************************************************************************/
int main(int argc, char* argv[]) {
	dzn::locator locator;
	dzn::runtime runtime;
	locator.set(runtime);

	SortingRobotSystem robbie_de_robot(locator);

	robbie_de_robot.check_bindings();

	// Initialize pins
	robbie_de_robot.led.led.in.initialise(MAIN_PUSHER_OUT_PIN); // TODO: Use correct pin.
	robbie_de_robot.sensor.sensor.in.initialise(MAIN_PRESENCE_IN_PIN); // TODO: Use correct pin.

	// Start the system! Just like Sten! <3
	robbie_de_robot.master.in.start();

	while (true) {
		std::cout << "step\n";
		robbie_de_robot.sensor.detect(); // Input sensor detection
		delay(500); // 500 ms
	}
	return 0;
}

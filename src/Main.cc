#include <dzn/runtime.hh>
#include <dzn/locator.hh>

#include "commutils.h"

#include "SortingRobot.hh"
#include <iostream>
#include "wiringPi.h"
#include <vector>
#include <string>
#include "config.hh"

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


void logState(SortingRobotSystem robo, std::vector<std::string> translation) {
    std::cout << "\n\n    [STATE] " << translation[robo.master.in.getState()] << "\n\n";
}

/*******************************************************************************
 * ENTRY POINT CODE
 ******************************************************************************/
int main(int argc, char* argv[]) {
    dzn::locator locator;
    dzn::runtime runtime;
    locator.set(runtime);

    std::vector<std::string> t = // translation
    {
    "Off", "Idle", " Waiting", "Error", "IngestingDisk", "Sorting"
    };

    // Initialize libmosquitto
    if (!setup_mqtt()) return 1;

    // Dezyne trigger variables
    bool fatalError = false;
    bool robotFailsFairness = false;

    int disk_taking = 1;

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

    // ENSURE ALL PINS TO LOW
    digitalWrite(MOVE_BELT_OUT_PIN, LOW);
    digitalWrite(MAIN_PUSHER_OUT_PIN, LOW);
    digitalWrite(WHITE_PUSHER_OUT_PIN, LOW);
    digitalWrite(BLACK_PUSHER_OUT_PIN, LOW);
    digitalWrite(STATUS_2_OUT_PIN, LOW);
    digitalWrite(STATUS_1_OUT_PIN, LOW);
    digitalWrite(STATUS_0_OUT_PIN, LOW);

    SortingRobotSystem robbie_de_robot(locator);

    robbie_de_robot.check_bindings();

    // Initialize pins on components
    robbie_de_robot.whiteActuator.actuator.in.initialise(WHITE_PUSHER_OUT_PIN);
    robbie_de_robot.blackActuator.actuator.in.initialise(BLACK_PUSHER_OUT_PIN);
    robbie_de_robot.wheelMotor.motor.in.initialise(MAIN_PUSHER_OUT_PIN);
    robbie_de_robot.beltMotor.motor.in.initialise(MOVE_BELT_OUT_PIN);

    robbie_de_robot.factorFloorSensor.sensor.in.initialise(MAIN_PRESENCE_IN_PIN);
    robbie_de_robot.wheelStopSensor.sensor.in.initialise(MAIN_PUSHER_ENDSTOP_IN_PIN);
    robbie_de_robot.cs.colourSensor.in.initialise(COLOR_SENSOR_0_IN_PIN, COLOR_SENSOR_1_IN_PIN);
    robbie_de_robot.beltSensorWhite.sensor.in.initialise(WHITE_SENSOR_IN_PIN);
    robbie_de_robot.beltSensorBlack.sensor.in.initialise(BLACK_SENSOR_IN_PIN);

    // Start the system! Just like Sten! <3
    robbie_de_robot.master.in.start();

    while (true) {
        // if (debug) {
        std::cout << "step\n";

        heartbeat();

        // TODO:
            // When we take disk, increment counter!

        //TODO: after taking a disk, publish the message
        if (disk_taking % 15 == 0) {
            take_disk();
        }
        disk_taking++;
        // TODO: what logic triggers fatalError = true? Determine what kind of
        // error would this be
        if (fatalError == true) {
            raise_emergency_stop();
        }

        // TODO: what logic triggers this? After detecting that our robot takes
        // "too many" or "too few" disks compared to the others
        if (robotFailsFairness == true) {
            raise_error();
        }




        logState(robbie_de_robot, t);
        // Check timers
        robbie_de_robot.ingestTimer.check_timer();
        logState(robbie_de_robot, t);
        robbie_de_robot.sortingTimer.check_timer();
        logState(robbie_de_robot, t);


        // Input sensor detection
        robbie_de_robot.factorFloorSensor.detect();
        logState(robbie_de_robot, t);

        robbie_de_robot.wheelStopSensor.detect();
        logState(robbie_de_robot, t);

        robbie_de_robot.cs.detect();
        logState(robbie_de_robot, t);

        robbie_de_robot.beltSensorWhite.detect();
        logState(robbie_de_robot, t);

        robbie_de_robot.beltSensorBlack.detect();
        logState(robbie_de_robot, t);

        std::cout << "post step\n";

        // Finally, update the external hearbeat counts to track how long we
        // haven't heard from other bots on the factory floor
        update_external_hearbeats();

        delay(1000); // 1000 ms
    }

    // Exiting program. Cleanup.
    destroy_mqtt();
    // TODO: wiringPi cleanup...

    return 0;
}

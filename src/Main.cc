#include <dzn/runtime.hh>
#include <dzn/locator.hh>
#include <iostream>
#include <vector>
#include <string>

#include "wiringPi.h"
#include "config.hh"
#include "utils.hh"

#include "Communicator.hh"
#include "StatusReporter.hh"
#include "SortingRobot.hh"


/*******************************************************************************
 * ENTRY POINT CODE
 ******************************************************************************/
int main(int argc, char* argv[]) {
    dzn::locator locator;
    dzn::runtime runtime;
    locator.set(runtime);

    SortingRobotSystem robbie_de_robot(locator);
    StatusReporter sr(Config::STATUS_0_OUT_PIN,
                      Config::STATUS_1_OUT_PIN,
                      Config::STATUS_2_OUT_PIN);

    // Initialize libmosquitto
    if (!setup_mqtt(&robbie_de_robot)) return 1;

    // Dezyne trigger variables
    bool fatalError = false;
    bool robotFailsFairness = false;

    /*******************************************************************************
     * Initial setup wiringPi
     ******************************************************************************/
    wiringPiSetup(); // Regular wiringPi pin mode setup

    // OUTPUT PINS
    pinMode(Config::MOVE_BELT_OUT_PIN, OUTPUT);
    pinMode(Config::MAIN_PUSHER_OUT_PIN, OUTPUT);
    pinMode(Config::WHITE_PUSHER_OUT_PIN, OUTPUT);
    pinMode(Config::BLACK_PUSHER_OUT_PIN, OUTPUT);

    pinMode(Config::STATUS_2_OUT_PIN, OUTPUT);
    pinMode(Config::STATUS_1_OUT_PIN, OUTPUT);
    pinMode(Config::STATUS_0_OUT_PIN, OUTPUT);

    // INPUT PINS
    pinMode(Config::MAIN_PRESENCE_IN_PIN, INPUT);
    pinMode(Config::MAIN_PUSHER_ENDSTOP_IN_PIN, INPUT);
    pinMode(Config::WHITE_SENSOR_IN_PIN, INPUT);
    pinMode(Config::BLACK_SENSOR_IN_PIN, INPUT);
    pinMode(Config::COLOR_SENSOR_0_IN_PIN, INPUT);
    pinMode(Config::COLOR_SENSOR_1_IN_PIN, INPUT);

    // ENSURE ALL PINS TO LOW
    digitalWrite(Config::MOVE_BELT_OUT_PIN, LOW);
    digitalWrite(Config::MAIN_PUSHER_OUT_PIN, LOW);
    digitalWrite(Config::WHITE_PUSHER_OUT_PIN, LOW);
    digitalWrite(Config::BLACK_PUSHER_OUT_PIN, LOW);
    digitalWrite(Config::STATUS_2_OUT_PIN, LOW);
    digitalWrite(Config::STATUS_1_OUT_PIN, LOW);
    digitalWrite(Config::STATUS_0_OUT_PIN, LOW);

    Communicator &comms = Communicator::getInstance();

    robbie_de_robot.check_bindings();

    // Initialize pins on components
    robbie_de_robot.whiteActuator.actuator.in.initialise(Config::WHITE_PUSHER_OUT_PIN);
    robbie_de_robot.blackActuator.actuator.in.initialise(Config::BLACK_PUSHER_OUT_PIN);
    robbie_de_robot.wheelMotor.motor.in.initialise(Config::MAIN_PUSHER_OUT_PIN);
    robbie_de_robot.beltMotor.motor.in.initialise(Config::MOVE_BELT_OUT_PIN);

    robbie_de_robot.factorFloorSensor.sensor.in.initialise(Config::MAIN_PRESENCE_IN_PIN);
    robbie_de_robot.wheelStopSensor.sensor.in.initialise(Config::MAIN_PUSHER_ENDSTOP_IN_PIN);
    robbie_de_robot.cs.colourSensor.in.initialise(Config::COLOR_SENSOR_0_IN_PIN, Config::COLOR_SENSOR_1_IN_PIN);
    robbie_de_robot.beltSensorWhite.sensor.in.initialise(Config::WHITE_SENSOR_IN_PIN);
    robbie_de_robot.beltSensorBlack.sensor.in.initialise(Config::BLACK_SENSOR_IN_PIN);

    // For additional tracking of the robot state
    int current_state = robbie_de_robot.master.in.getState();

    while (true) {
        // if (debug) {
        std::cout << "step\n";

        if (Config::DEBUG) {
            std::cout << "system_started: " << comms.system_started << '\n';
            std::cout << "system_start  : " << comms.system_start_requested << '\n';
            std::cout << "system_stop   : " << comms.system_stop_requested << '\n';
            std::cout << "system_state  : " << robbie_de_robot.master.in.getState() << '\n';
        }

        // ====================================
        // Check if we are requested to pull the emergency breaks
        // ====================================
        // TODO: test with the robot functioning for real
        if (comms.system_emergency_stop_requested || (comms.system_emergency_stopped && !comms.system_start_requested)) {
            if (!comms.system_emergency_stopped) {
                robbie_de_robot.master.in.emergency();
                robbie_de_robot.master.in.stop();
                comms.system_emergency_stopped = true;
                comms.system_started = false; // Flag we started the system
                comms.system_emergency_stop_requested = false; // Remove the flag for the request
            }
            delay(1000);
            continue;
        }

        // Stayin' alive 'live 'live 'live staaaayin alliiiiive
        comms.heartbeat();

        // ====================================
        // Before system is started logic
        // ====================================
        if (!comms.system_started) {
            if (!comms.system_start_requested) {
                delay(1000);
                continue;
            } else {
                robbie_de_robot.master.in.start();
                comms.system_started = true; // Flag we started the system
                comms.system_start_requested = false; // Remove the flag for the request
            }
        }

        // ====================================
        // Check if we are requested to stop
        // ====================================
        if (comms.system_stop_requested) {
            current_state = robbie_de_robot.master.in.getState();
            if (current_state == 1) {
                robbie_de_robot.master.in.stop();
                comms.system_stop_requested = false;
                comms.system_started = false;
                continue; // Reset to start of loop
            }
        }

        // ====================================
        // When system is started, first check if we need to wait, i.e., is the scenario fair?
        // ====================================
        // TODO: we should test this more thoroughly...
        if (comms.should_wait()) { // Fairness test
            robbie_de_robot.master.in.forceWait();
            continue; // Reset to start of loop
        } else {
            current_state = robbie_de_robot.master.in.getState();
            if (current_state == 2) {  // == "Waiting"
                robbie_de_robot.master.in.cancelWait();
                continue;
            }
        }

        // ====================================
        // The system is started and scenario is fair, thus do all below
        // ====================================

        current_state = robbie_de_robot.master.in.getState();
        if (current_state == 4) { // IngestingDisk
            // Check if we are done ingesting a disk
            // if so, we took a disk!
            if (robbie_de_robot.ingestTimer.check_timer()) {
                comms.take_disk();
            }
        }

        // TODO: what logic triggers fatalError = true? Determine what kind of
        // error would this be
        // TODO: hook in additional timeout timers .....
        if (fatalError == true) {
            comms.raise_emergency();
        }

        // TODO: what logic triggers this? After detecting that our robot takes
        // "too many" or "too few" disks compared to the others
        if (robotFailsFairness == true) {
            comms.raise_error();
        }

        current_state = robbie_de_robot.master.in.getState();
        if (current_state == 5) { // "SortingDisk"
            robbie_de_robot.sortingTimer.check_timer();
        }

        // ====================================
        // Input sensor detection
        // ====================================
        // Testing and triggering the sensors
        // which in turn can trigger system state transistions
        robbie_de_robot.factorFloorSensor.detect();
        robbie_de_robot.wheelStopSensor.detect();
        robbie_de_robot.cs.detect(); // color sensor
        robbie_de_robot.beltSensorWhite.detect();
        robbie_de_robot.beltSensorBlack.detect();

        // Finally, update the external hearbeat counts to track how long we
        // haven't heard from other bots on the factory floor
        comms.update_external_hearbeats();

        delay(1000); // 1000 ms
    }

    // Exiting program. Cleanup.
    comms.destroy_mqtt();
    // TODO: wiringPi cleanup...

    return 0;
}

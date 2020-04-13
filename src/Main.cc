#include <dzn/runtime.hh>
#include <dzn/locator.hh>
#include <iostream>
#include <vector>
#include <string>

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
    Communicator &comms = Communicator::getInstance();

    // Initialize libmosquitto and wiringPi
    if (!setup_mqtt(&robbie_de_robot)) return 1;
    if (!setup_wiring(&robbie_de_robot)) return 2;

    // Dezyne trigger variables
    bool fatalError = false;
    bool robotFailsFairness = false;

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

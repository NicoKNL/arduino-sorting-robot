//DBL Embedded Systems, group NotFullNerds
#include "commutils.h"

#include <wiringPi.h>
#include <iostream>

int main(int argc, char *argv[]) {
    // Initialize libmosquitto
    if (!setup_mqtt()) return 1;

    request_disks_taken();

    // Dezyne trigger variables
    bool fatalError = false;
    bool robotFailsFairness = false;


    //Main loop
    while (true) {
        // if (debug) {
        std::cout << "loop\n";
        heartbeat();

        // TODO:
            // When we take disk, increment counter!

        //TODO: after taking a disk, publish the message
        take_disk();

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

        // Finally, update the external hearbeat counts to track how long we
        // haven't heard from other bots on the factory floor
        update_external_hearbeats();
        delay(1000);
    }

    // Exiting program. Cleanup.
    destroy_mqtt();
    // TODO: wiringPi cleanup...

    return 0;
}

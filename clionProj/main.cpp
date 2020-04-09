//DBL Embedded Systems, group NotFullNerds
// #include "mqtt.h"
#include <wiringPi.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <mosquitto.h>
#include <string>
#include <sstream>

// const char * BROKER_ADDRESS = "86.91.204.180";
const char * BROKER_ADDRESS = "127.0.0.1";
const int MQTT_PORT = 1883;
// const int MQTT_PORT = 23321;

const char * MQTT_TOPIC_IN = "factory/robot0/in";
const char * MQTT_TOPIC_OUT = "factory/robot0/out";
const int OUR_ROBOT_ID = 3;
const int KEEPALIVE = 60;
const int HEARTBEAT_DELAY = 5;
const int MAX_HEARTBEAT_DELAY = 5; // TODO: Change back to 60

int HEARTBEAT_TRACKER = 0;
std::vector<bool> EXTERNAL_ALIVE = {0, 1, 1, 1, 1};
std::vector<int> EXTERNAL_HEARTBEAT_CHECKER = {-10, -10, -10, -10, -10}; // We're being gracious here...
std::vector<int> DISKS_TAKEN = {0, 0, 0, 0, 0};
std::vector<int> DISK_COUNTERS = {0, 0, 0, 0, 0}; // We probably don't care about this

bool requested_disks_taken = false;

mosquitto* mosq;

void send_message(std::string message) {
    mosquitto_publish(mosq, nullptr, MQTT_TOPIC_OUT, message.length(), message.c_str(), 0, false);
}

void heartbeat() {
    if (HEARTBEAT_TRACKER % HEARTBEAT_DELAY == 0) {
        send_message("hearbeat" + std::to_string(OUR_ROBOT_ID));
    }
    ++HEARTBEAT_TRACKER;
}

void take_disk() {
    send_message("tookDisk:" + std::to_string(OUR_ROBOT_ID));
}

void raise_emergency_stop() {
    send_message("emergencyStop");
}

void raise_error() {
    send_message("error:" + std::to_string(OUR_ROBOT_ID));
}

void request_disk_counters() {
    send_message("requestDiskCounters");
}

void request_disks_taken() {
    requested_disks_taken = true;

    // Reset disk counters as apparently, we have no clueee
    for (int i = 1; i < 5; ++i) {
        DISKS_TAKEN[i] = 0;
    }


    // This method is for recovering. See final paragraph in protocol docs.
    send_message("requestDisksTaken:" + std::to_string(OUR_ROBOT_ID));
}

void respond_disks_taken() {
    send_message("respondDisksTaken:" +
            std::to_string(OUR_ROBOT_ID) + "," +
            std::to_string(DISKS_TAKEN[1]) + "," +
            std::to_string(DISKS_TAKEN[2]) + "," +
            std::to_string(DISKS_TAKEN[3]) + "," +
            std::to_string(DISKS_TAKEN[4]));
}

void update_external_hearbeats() {
    for (int i = 1; i < 5; ++i) {
        // Skip for our own robot.
        if (i == OUR_ROBOT_ID) {
          continue;
        }

        if (EXTERNAL_ALIVE[i]) {
            ++EXTERNAL_HEARTBEAT_CHECKER[i];
            if (EXTERNAL_HEARTBEAT_CHECKER[i] >= MAX_HEARTBEAT_DELAY) {
                EXTERNAL_ALIVE[i] = false;
                std::cout << "[INFO] External robot died: " << i << '\n';
            }
        }
    }
}

bool setup_mqtt() {
    mosquitto_lib_init();
    mosq = mosquitto_new(nullptr, true, nullptr);

    if (!mosq) {
        fprintf(stderr, "MQTT Error: Out of memory.\n");
        return false;
    }

    mosquitto_message_callback_set(mosq, [](mosquitto* _mosq, void* obj, const mosquitto_message* msg) {
        if (!msg->payloadlen) {
            fprintf(stderr, "MQTT Error: malformed message length received.\n");
            return;
        }

        // Get message
        char* payload = (char*) msg->payload;

        // Convert to std string
        std::string message;
        message += payload;

        // Debugging TODO: wrap in debug statement
        std::cout << message << '\n';

        char strCounter[100];

        if (message.find("heartbeat") == 0) {
            // whose hearbeat is it?
            int external_robot_id = message[9] - '0';
            std::cout << external_robot_id << '\n';

            // Only keep track of robots that are announced as alive
            if (EXTERNAL_ALIVE[external_robot_id] && external_robot_id != OUR_ROBOT_ID) {
                EXTERNAL_HEARTBEAT_CHECKER[external_robot_id] = 0;
            }
        }
        else if (message.find("start") == 0) {
            //start the robot, sth like
            //robbie_de_robot.master.in.start();
            std::cout << "[INFO] Received start\n";
        }
        else if (message.find("stop") == 0) {
            //wait with sleep() or check some pins to know when the system finished sorting
            //then stop
            std::cout << "[INFO] Received stop\n";
        }
        else if (message.find("emergencyStop") == 0) {
            std::cout << "[INFO] Received emergency stop\n";
        }
        else if (message.find("tookDisk") == 0) {
            int external_robot_id = message[9] - '0';
            // Does tookDisk redirect to our channel???
            ++DISKS_TAKEN[external_robot_id];

        }
        else if (message.find("requestDisksTaken") == 0) {
            if (!requested_disks_taken) {
                std::cout << " responding ..... \n";
                respond_disks_taken();
            }
        }
        else if (message.find("respondDiskCounters") == 0) {
            //hacky way: otherwise the nr of disks in the end
            //from the last robot, are not taken into account
            std::cout << "[INFO] Received respondDiskCounters\n";

            std::stringstream ss(message.substr(20));
            std::string tmp;

            int i = 1;
            while (std::getline(ss, tmp, ',')) {
                DISK_COUNTERS[i] = std::stoi(tmp);
                ++i;
            }

            // TODO: if debug
            for (int j = 1; j < 5; j++) {
                std::cout << DISK_COUNTERS[j] << ", ";
            }
            std::cout << '\n';
        }
        else if (message.find("respondDisksTaken") == 0) {
            if (requested_disks_taken) {
                //TODO: from this message, fairness can be derived/defined
                std::cout << "Received respondDisksTaken\n";

                std::stringstream ss(message.substr(20));
                std::string tmp;

                std::cout << "SANITY CHECK: " << message.substr(20) << '\n';

                int i = 1;
                while (std::getline(ss, tmp, ',')) {
                    DISKS_TAKEN[i] = std::max(DISKS_TAKEN[i], std::stoi(tmp));
                    ++i;
                }

                // TODO: if debug
                for (int j = 1; j < 5; j++) {
                    std::cout << DISKS_TAKEN[j] << ", ";
                }
                std::cout << '\n';

                requested_disks_taken = false;
            }

            //if the method from respondDiskCounters works, just copy here and change array name in the end"
            //TODO: if "fair", call method to take/sort disks
            //calls a method/modifies pins from Dezyne Main.cc
        }

    });

    if (mosquitto_connect_async(mosq, BROKER_ADDRESS, MQTT_PORT, KEEPALIVE) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "MQTT Error: could not establish connection.\n");
        return false;
    }

    mosquitto_subscribe(mosq, nullptr, MQTT_TOPIC_IN, 0);
    mosquitto_loop_start(mosq);

    return true;
}

void destroy_mqtt() {
    mosquitto_disconnect(mosq);
    mosquitto_loop_stop(mosq, true);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
}

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

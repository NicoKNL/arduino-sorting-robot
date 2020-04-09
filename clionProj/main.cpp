//DBL Embedded Systems, group NotFullNerds
// #include "mqtt.h"
#include <wiringPi.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <mosquitto.h>
#include <string>
#include <sstream>
// #include <cmath>

// const char * BROKER_ADDRESS "86.91.204.180"
const char * BROKER_ADDRESS = "127.0.0.1";
const int MQTT_PORT = 1883;
// #define MQTT_PORT 23321

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
    // Reset disk counters as apparently, we have no clueee
    for (int i = 1; i < 5; ++i) {
        DISKS_TAKEN[i] = 0;
    }

    // This method is for recovering. See final paragraph in protocol docs.
    send_message("requestDisksTaken:" + std::to_string(OUR_ROBOT_ID));
    requested_disks_taken = true;
}

void respond_disks_taken() {
    send_message("respondDisksTaken:" +
            std::to_string(OUR_ROBOT_ID) +
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

                std::stringstream ss(message.substr(18));
                std::string tmp;

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

void initialHearbeatSync() {
    // while (true) {
      // 1. Check for initial heartbeats to see which robots are on the factory floor
      // 2. Occasionally send out our own hearbeat according to the protocol
    // }
    return;
}
//
// bool checkEmergencyStop(const mqtt_client * handler) {
//     return false;
// }
//
// void checkHeartbeats(const mqtt_client * handler) {
//     return;
// }

int main(int argc, char *argv[]) {
    // Initialize libmosquitto
    if (!setup_mqtt()) return 1;

    request_disks_taken();

    // // Functional programming return storage objects
    char msg_out[255];// the output message (?)

    // Setup the mqtt client
    // mqtt_client * handler = new mqtt_client(OUR_ROBOT_ID, BROKER_ADDRESS, MQTT_PORT);

    // Dezyne trigger variables
    bool fatalError = false;
    bool robotFailsFairness = false;

    // initialHearbeatSync(handler);

    //Main loop
    while (true) {
        std::cout << "loop\n";
        heartbeat();

        // TODO:
            // When we take disk, increment counter!

        //how is this actually useful?
        //check how many disks have passed in front of each robot (so not necessarily processed))
        //send this every few seconds, or whenever a message is received?

        // How many disks have been seen by other robots on the factory belt individually
        // strcpy(msg_out, "requestDiskCounters");
        // handler->publish(NULL, MQTT_TOPIC_OUT, strlen(msg_out), msg_out);
        // std::cout << "message sent...\n";
        //TODO: Send signal: take more disks (based on fairness) (if or while loop)

        // // Request to get an overview of the number of disks taken by each robot
        // // on the factory belt. This will be used for the fairness principle.
        // strcpy(msg_out, REQUEST_DISKS_TAKEN);
        // mosquitto_publish(mosq, nullptr, MQTT_TOPIC_OUT, strlen(msg_out), msg_out, 0, false);

        //
        //
        // //TODO: after taking a disk, publish the message
        // //(as soon as it arrives, the broker increases the counter for the corresponding robot)
        // strcpy(msg_out, "tookDisk: A");
        // handler->publish(NULL, MQTT_TOPIC_OUT, strlen(msg_out), msg_out);
        //
        // //determine what kind of error would this be
        // if (fatalError == true) {
        //     strcpy(msg_out, "emergency");
        //     handler->publish(NULL, MQTT_TOPIC_OUT, strlen(msg_out), msg_out);
        // }
        //
        // //after detecting that our robot takes "too many" or "too few" disks compared to the others
        // if (robotFailsFairness == true) {
        //     strcpy(msg_out, "error: <our_robot_ID> ");
        //     handler->publish(NULL, MQTT_TOPIC_OUT, strlen(msg_out), msg_out);
        // }
        //
        // strcpy(msg_out, "tookDisk: B");

        // handler->publish(NULL, "factory/robot1/in", strlen(tstr),
                         // tstr);    // Publish the data to MQTT topic "IGoT/sensors"



        // mosquitto_message msg_out;
        // handler->subscribe(&msg_out);
        // char * message;
        // handler->check_messages(message);
        // std::cout << message << '\n';
        //deprecated, might not even need this
        update_external_hearbeats();
        delay(1000);
        // sleep(1e5);
    }

    // mosqpp::lib_cleanup();

    return 0;
}

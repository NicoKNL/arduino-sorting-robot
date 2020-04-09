//DBL Embedded Systems, group NotFullNerds
// #include "mqtt.h"
#include <wiringPi.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <mosquitto.h>
#include <string>

// const char * BROKER_ADDRESS "86.91.204.180"
const char * BROKER_ADDRESS = "127.0.0.1";
const int MQTT_PORT = 1883;
// #define MQTT_PORT 23321

const char * MQTT_TOPIC_IN = "factory/robot0/in";
const char * MQTT_TOPIC_OUT = "factory/robot0/out";
const int ROBOT_ID = 3;
const int KEEPALIVE = 60;
const int HEARTBEAT_DELAY = 5;
mosquitto* mosq;

int HEARTBEAT_TRACKER = 0;

const char * REQUEST_DISKS_TAKEN = "requestDisksTaken:3";
// struct mosquitto_message{
// 	int mid;
// 	char *topic;
// 	void *payload;
// 	int payloadlen;
// 	int qos;
// 	bool retain;
// };

void send_message(std::string message) {
    mosquitto_publish(mosq, nullptr, MQTT_TOPIC_OUT, message.length(), message.c_str(), 0, false);
}

void heartbeat() {
    std::cout << "hearbeat\n";
    if (HEARTBEAT_TRACKER % HEARTBEAT_DELAY == 0) {
        send_message("hearbeat" + std::to_string(ROBOT_ID));
    }
    ++HEARTBEAT_TRACKER;
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

        char* payload = (char*) msg->payload;

        std::cout << payload << '\n';

        char strCounter[100];

        if (true) {
            return;
        }
        else if (strcmp(strCounter, "start") == 0) {
            //start the robot, sth like
            //robbie_de_robot.master.in.start();
            std::cout << "Received start\n";
        }
        else if (strcmp(strCounter, "stop") == 0) {
            //wait with sleep() or check some pins to know when the system finished sorting
            //then stop
            std::cout << "Received stop\n";
        }
        else if (strcmp(strCounter, "respondDiskCounters") == 0) {
            //hacky way: otherwise the nr of disks in the end
            //from the last robot, are not taken into account
            std::cout << "Received respondDiskCounters\n";

            // //TODO: test that this method for extracting number of disks per robot into an array works
            // strCounter[strlen(strCounter) + 1] = ',';
            //
            // int DisksPerRobot[NROF_ROBOTS + 1];
            // int robotCounter = 0;
            // for (int i = 0; i < strlen(tstr); i++) {
            //     if (tstr[i] == ':') {
            //         int begin = i + 1;
            //         int end = i + 1;
            //         bool found = false;
            //
            //         while (end < strlen(tstr) - 1) {
            //             if (tstr[end + 1] == ',') {
            //                 found = true;
            //             } else end++;
            //             if (found = true) {
            //                 char s[255];
            //                 int count = 0;
            //                 for (int index = begin; index <= end; t++) {
            //                     s[count++] = tstr[index];
            //                 }
            //                 //convert disks that robot has to int
            //                 //then put into the corresponding array
            //                 int numberOfDisks = atol(s);
            //                 DisksPerRobot[robotCounter++];
            //                 //continue the initial loop
            //                 found = false;
            //                 end++;
            //             }
            //         }
            //     }
            //     break;
            // }
            // for (int i = 0; i < robotCounter; i++) {
            //     cout << DisksPerRobot[i] <<' ';
            // }

        }
        else if (strcmp(strCounter, "respondDisksTaken") == 0) {
            //TODO: from this message, fairness can be derived/defined
            std::cout << "Received respondDisksTaken\n";

            //if the method from respondDiskCounters works, just copy here and change array name in the end"
            //TODO: if "fair", call method to take/sort disks
            //calls a method/modifies pins from Dezyne Main.cc
        }

    });

    if (mosquitto_connect_async(mosq, BROKER_ADDRESS, MQTT_PORT, KEEPALIVE) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "MQTT Error: could not establish connection.\n");
        return false;
    }

    mosquitto_subscribe(mosq, nullptr, "factory/robot0/in", 0);
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

    // // Functional programming return storage objects
    char msg_out[255];// the output message (?)

    // Setup the mqtt client
    // mqtt_client * handler = new mqtt_client(ROBOT_ID, BROKER_ADDRESS, MQTT_PORT);

    // Dezyne trigger variables
    bool fatalError = false;
    bool robotFailsFairness = false;

    // initialHearbeatSync(handler);

    //Main loop
    while (true) {
        std::cout << "loop\n";
        heartbeat();


        // rc = handler->loop();                        // Keep MQTT connection
        // std::cout << rc << ", " << MOSQ_ERR_SUCCESS << '\n';
        // if (!MOSQ_ERR_SUCCESS)
        //     handler->reconnect();
        // else {
        //
        //     handler->on_subscribe(0, 0, NULL);
        // }

        // Check if we need to perform an emergency stop
        // checkEmergencyStop(handler);

        // Check hearbeats
        // checkHeartbeats(handler);

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
        strcpy(msg_out, REQUEST_DISKS_TAKEN);
        mosquitto_publish(mosq, nullptr, MQTT_TOPIC_OUT, strlen(msg_out), msg_out, 0, false);

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
        delay(1000);
        // sleep(1e5);
    }

    // mosqpp::lib_cleanup();

    return 0;
}

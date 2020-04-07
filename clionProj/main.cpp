//DBL Embedded Systems, group NotFullNerds
#include "mqtt.h"
#include <wiringPi.h>
#include <iostream>
#include <vector>

#define BROKER_ADDRESS "86.91.204.180"
#define MQTT_PORT 1883
#define MQTT_TOPIC_IN "factory/robot0/in"
#define MQTT_TOPIC_OUT "factory/robot0/in"
#define ROBOT_ID "3"


// struct mosquitto_message{
// 	int mid;
// 	char *topic;
// 	void *payload;
// 	int payloadlen;
// 	int qos;
// 	bool retain;
// };

void initialHearbeatSync(const mqtt_client * handler) {
    while (true) {
      // 1. Check for initial heartbeats to see which robots are on the factory floor
      // 2. Occasionally send out our own hearbeat according to the protocol
    }
    return;
}

bool checkEmergencyStop(const mqtt_client * handler) {
    return false;
}

void checkHeartbeats(const mqtt_client * handler) {
    return;
}

int main(int argc, char *argv[]) {
    // Initialize libmosquitto
    int rc = 0;   // the return code
    rc = mosqpp::lib_init();

    if (rc != MOSQ_ERR_SUCCESS) {
      // do stuff
    }

    // Functional programming return storage objects
    char client_id[255];
    char msg_out[255];// the output message (?)

    // Setup the mqtt client
    mqtt_client * handler = new mqtt_client(client_id, BROKER_ADDRESS, MQTT_PORT, MQTT_TOPIC_IN, MQTT_TOPIC_OUT);

    // Dezyne trigger variables
    bool fatalError = false;
    bool robotFailsFairness = false;

    // initialHearbeatSync(handler);

    //Main loop
    while (true) {
        rc = handler->loop();                        // Keep MQTT connection
        if (!MOSQ_ERR_SUCCESS)
            handler->reconnect();
        else {
            handler->on_subscribe(0, 0, NULL);
        }

        // Check if we need to perform an emergency stop
        // checkEmergencyStop(handler);

        // Check hearbeats
        // checkHeartbeats(handler);

        //how is this actually useful?
        //check how many disks have passed in front of each robot (so not necessarily processed))
        //send this every few seconds, or whenever a message is received?

        // How many disks have been seen by other robots on the factory belt individually
        /* strcpy(tstr, "requestDiskCounters");
         handler->publish(NULL, "factory/robot1/in/", strlen(tstr), tstr); */

        //TODO: Send signal: take more disks (based on fairness) (if or while loop)

        // // Request to get an overview of the number of disks taken by each robot
        // // on the factory belt. This will be used for the fairness principle.
        // strcpy(msg_out, strcat("requestDisksTaken:", ROBOT_ID));
        // handler->publish(NULL, MQTT_TOPIC_OUT, strlen(msg_out), msg_out);
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
        char * message;
        handler->check_messages(message);
        std::cout << message << '\n';
        //deprecated, might not even need this
        delay(1000);
        // sleep(1e5);
    }

    mosqpp::lib_cleanup();

    return 0;
}

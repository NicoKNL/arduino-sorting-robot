//DBL Embedded Systems, group NotFullNerds
#include "mqtt.h"
#include <wiringPi.h>
#include <iostream>

#define CLIENT_ID "Client_ID"
#define BROKER_ADDRESS "86.91.204.180"
#define MQTT_PORT 1883
#define MQTT_TOPIC "EXAMPLE_TOPIC"

// struct mosquitto_message{
// 	int mid;
// 	char *topic;
// 	void *payload;
// 	int payloadlen;
// 	int qos;
// 	bool retain;
// };

int main(int argc, char *argv[]) {

    //the client and the return code
    class mqtt_client * mqttHdl;
    int rc = 0;

    bool fatalError = false;
    bool robotFailsFairness = false;

    //mosqpp::
    mosqpp::lib_init();			// Initialize libmosquitto

    /*if (argc > 1)
        strcpy (host, argv[1]);*/

    mqttHdl = new mqtt_client(CLIENT_ID, BROKER_ADDRESS, MQTT_PORT);

    //test string = Payload
    char tstr[255];

    //Main loop
    while (true) {
        //fd = open(NRMK_SMEM_NAME, O_RDWR, S_IRUSR | S_IWUSR);    // Open Shared Memory
        //res = read(fd, 1111, FILE_LENGTH);

        //how is this actually useful?
        //check how many disks have passed in front of each robot (so not necessarily processed))
        //send this every few seconds, or whenever a message is received?
        // strcpy(tstr, "requestDiskCounters");
        // mqttHdl->publish(NULL, "factory/robot1/in/", strlen(tstr), tstr);

        //TODO: Send signal: take more disks (based on fairness) (if or while loop)
        strcpy(tstr, "requestDisksTaken: <our_robot_ID> ");
        mqttHdl->publish(NULL, "factory/robot1/in", strlen(tstr), tstr);


        //TODO: after taking a disk, publish the message
        //(as soon as it arrives, the broker increases the counter for the corresponding robot)
        strcpy(tstr, "tookDisk: A");
        mqttHdl->publish(NULL, "factory/robot1/out", strlen(tstr), tstr);

        //determine what kind of error would this be
        if (fatalError == true) {
            strcpy(tstr, "emergency");
            mqttHdl->publish(NULL, "predefined_Topic/", strlen(tstr), tstr);
        }

        //after detecting that our robot takes "too many" or "too few" disks compared to the others
        if (robotFailsFairness == true) {
            strcpy(tstr, "error: <our_robot_ID> ");
            mqttHdl->publish(NULL, "predefined_Topic/", strlen(tstr), tstr);
        }

        strcpy(tstr, "tookDisk: B");

        // mqttHdl->publish(NULL, "factory/robot1/in", strlen(tstr),
                         // tstr);    // Publish the data to MQTT topic "IGoT/sensors"

        rc = mqttHdl->loop();                        // Keep MQTT connection
        if (rc)
            mqttHdl->reconnect();
        else {
            mqttHdl->on_subscribe(0, 0, NULL);
        }

        mosquitto_message msg;
        mqttHdl->subscribe(&msg);
        std::cout << msg << '\n';
        //deprecated, might not even need this
        delay(1000);
        // sleep(1e5);
    }

    mosqpp::lib_cleanup();

    return 0;
}

//DBL Embedded Systems, group NotFullNerds
#include "mqtt.h"
#include <iostream>
#include <cstring>
using namespace std;
#define NROF_ROBOTS 5
#define our_robot_ID 2

mqtt_client::mqtt_client(const char *id, const char *host, int port) : mosquittopp(id)
{

    int keepalive = DEFAULT_KEEP_ALIVE; // seconds

    //Wait for Sten's host and port info
    //mosqpp::
    connect(host, port, keepalive);		// Connect to MQTT Broker
}

mqtt_client::~mqtt_client()
{
}

void mqtt_client::on_connect(int rc)
{
    printf("Connected with code %d. \n", rc);

    if (rc == 0)
    {
        subscribe(NULL, "command/IGot");
    }
}

void mqtt_client:on_message(const struct mosquitto_message *message) {

    //message stored here
    char strCounter[DEFAULT_MAX_MESSAGE];

    //needs to be connected to the corresponding methods in Dezyne
    //sort of from dezyne, our project Main.cc
    if (strcmp(strCounter, "start") == 0) {
        //start the robot, sth like
        //robbie_de_robot.master.in.start();
        cout << "Received start" << endl;
    }
    else if (strcmp(strCounter, "stop") == 0) {
        //wait with sleep() or check some pins to know when the system finished sorting
        //then stop
        cout << "Received stop" << endl;
    }
    else if (strcmp(strCounter, "respondDiskCounters") == 0) {
        //hacky way: otherwise the nr of disks in the end
        //from the last robot, are not taken into account
        cout << "Received respondDiskCounters" << endl;

        //TODO: test that this method for extracting number of disks per robot into an array works
        /*strCounter[strlen(strCounter) + 1] = ',';

        int DisksPerRobot[NROF_ROBOTS + 1];
        int robotCounter = 0;
        for (int i = 0; i < strlen(tstr); i++) {
            if (tstr[i] == ':') {
                int begin = i + 1;
                int end = i + 1;
                bool found = false;

                while (end < strlen(tstr) - 1) {
                    if (tstr[end + 1] == ',') {
                        found = true;
                    } else end++;
                    if (found = true) {
                        char s[255];
                        int count = 0;
                        for (int index = begin; index <= end; t++) {
                            s[count++] = tstr[index];
                        }
                        //convert disks that robot has to int
                        //then put into the corresponding array
                        int numberOfDisks = atol(s);
                        DisksPerRobot[robotCounter++];
                        //continue the initial loop
                        found = false;
                        end++;
                    }
                }
            }
            break;
        }
        for (int i = 0; i < robotCounter; i++) {
            cout << DisksPerRobot[i] <<' ';
        }*/

    }
    else if (strcmp(strCounter, "respondDisksTaken") == 0) {
        //TODO: from this message, fairness can be derived/defined
        cout << "Received respondDisksTaken" << endl;

        //if the method from respondDiskCounters works, just copy here and change array name in the end"
        //TODO: if "fair", call method to take/sort disks
        //calls a method/modifies pins from Dezyne Main.cc
    }
};

void mqtt_client::on_subscribe(int mid, int qos_count, const int *granted_qos)
{
    printf("Subscription succeeded. \n");
}
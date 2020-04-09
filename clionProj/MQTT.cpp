//DBL Embedded Systems, group NotFullNerds
#include "mqtt.h"
#include <iostream>
#include <cstring>

#define NROF_ROBOTS 4
#define our_robot_ID 2

mqtt_client::mqtt_client(const char *id, const char *host, int port) : mosquittopp(id)
{
    // strcpy(m_topic_out, out);
    // strcpy(m_topic_in, in);
    m_port = port;
    int keepalive = DEFAULT_KEEP_ALIVE; // seconds
    connect(host, port, keepalive); // Connect to MQTT Broker
}

mqtt_client::~mqtt_client()
{
}

void mqtt_client::on_connect(int rc)
{
    printf("Connected with code %d. \n", rc);

    // if (rc == MOSQ_ERR_SUCCESS)
    // {
    //     // subscribe(NULL, m_topic_in);
    //     subscribe(NULL, m_topic_in);
    // }
}

void mqtt_client::on_message(const struct mosquitto_message *message) {

    //message stored here
    char strCounter[DEFAULT_MAX_MESSAGE];

    //needs to be connected to the corresponding methods in Dezyne
    //sort of from dezyne, our project Main.cc
    if (strcmp(strCounter, "start") == 0) {
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

        //TODO: test that this method for extracting number of disks per robot into an array works
        strCounter[strlen(strCounter) + 1] = ',';

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
        }

    }
    else if (strcmp(strCounter, "respondDisksTaken") == 0) {
        //TODO: from this message, fairness can be derived/defined
        std::cout << "Received respondDisksTaken\n";

        //if the method from respondDiskCounters works, just copy here and change array name in the end"
        //TODO: if "fair", call method to take/sort disks
        //calls a method/modifies pins from Dezyne Main.cc
    }
};

void mqtt_client::on_subscribe(int mid, int qos_count, const int *granted_qos)
{
    printf("Robbie_de_robot his subscription succeeded.\n");
}

void mqtt_client::check_messages(char *message) {
    return;
    // messages	pointer to a “struct mosquitto_message *”.  The received messages will be returned here.  On error, this will be set to NULL.
    // msg_count	the number of messages to retrieve.
    // want_retained	if set to true, stale retained messages will be treated as normal messages with regards to msg_count.  If set to false, they will be ignored.
    // topic	the subscription topic to use (wildcards are allowed).
    // qos	the qos to use for the subscription.
    // host	the broker to connect to.
    // port	the network port the broker is listening on.
    // client_id	the client id to use, or NULL if a random client id should be generated.
    // keepalive	the MQTT keepalive value.
    // clean_session	the MQTT clean session flag.
    // username	the username string, or NULL for no username authentication.
    // password	the password string, or NULL for an empty password.
    // will	a libmosquitto_will struct containing will information, or NULL for no will.
    // tls	a libmosquitto_tls struct containing TLS related parameters, or NULL for no use of TLS.

    // Note: want_retained must perhaps be set to true
    subscribe_simple(&m_message,
                     1,
                     false,
                     m_topic_out,
                     0,
                     m_host,
                     m_port,
                     m_id,
                     DEFAULT_KEEP_ALIVE,
                     true,
                     NULL,
                     NULL,
                     NULL,
                     NULL);
   	printf("%s %s\n", m_message->topic, (char *)m_message->payload);
    strcpy(message, (char*)m_message->payload);
}

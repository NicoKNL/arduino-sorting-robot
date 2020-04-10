//DBL Embedded Systems, group NotFullNerds
#ifndef COMMUTILS_HH
#define COMMUTILS_HH

#include <mosquitto.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>

class Communicator {
public:
    // const char * BROKER_ADDRESS = "86.91.204.180";
    const std::string BROKER_ADDRESS = "127.0.0.1";
    const int MQTT_PORT = 1883;
    // const int MQTT_PORT = 23321;

    const std::string MQTT_TOPIC_IN = "factory/robot2/in";
    const std::string MQTT_TOPIC_OUT = "factory/robot2/out";
    const int KEEPALIVE = 60;

private:

    const int OUR_ROBOT_ID = 2;
    const int HEARTBEAT_DELAY = 5;
    const int MAX_HEARTBEAT_DELAY = 5; // TODO: Change back to 60

    int HEARTBEAT_TRACKER = 0;
    std::vector<bool> EXTERNAL_ALIVE = {0, 1, 1, 1, 1};
    std::vector<int> EXTERNAL_HEARTBEAT_CHECKER = {-10, -10, -10, -10, -10}; // We're being gracious here...
    std::vector<int> DISKS_TAKEN = {0, 0, 0, 0, 0};
    std::vector<int> DISK_COUNTERS = {0, 0, 0, 0, 0}; // We probably don't care about this

    bool requested_disks_taken = false;

    mosquitto* mosq;

public:
    static Communicator& getInstance() {
        static Communicator instance;
        return instance;
    };

    Communicator(Communicator const&) = delete;

    void operator=(Communicator const&) = delete;


        void set_mosq(mosquitto * mosq);

        void send_message(std::string message);

        void heartbeat();

        void take_disk();

        void raise_emergency_stop();

        void raise_error();

        void request_disk_counters();

        void request_disks_taken();

        void respond_disks_taken();

        void update_external_hearbeats();

        void destroy_mqtt();

        void handle_message(std::string message);
private:
    Communicator(){};
};



#endif //COMMUTILS_HH

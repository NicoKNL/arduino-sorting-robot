#include <mosquitto.h>
#include "SortingRobot.hh"
#include "Communicator.hh"

bool setup_mqtt(SortingRobotSystem *robo) {
    mosquitto_lib_init();

    Communicator &comms = Communicator::getInstance();

    // First arg here const char* with ID
    mosquitto* mosq = mosquitto_new(nullptr, true, nullptr);

    if (!mosq) {
        fprintf(stderr, "MQTT Error: Out of memory.\n");
        return false;
    }

    comms.set_mosq(mosq);
    comms.set_robot(robo);

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

        if (Config::DEBUG) {
            std::cout << "[INCOMING MESSAGE] " << message << '\n';
        }

        Communicator &comms = Communicator::getInstance();
        comms.handle_message(message);
    });

    if (mosquitto_connect_async(mosq, comms.BROKER_ADDRESS.c_str(), comms.MQTT_PORT, comms.KEEPALIVE) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "[ERROR] MQTT could not establish connection.\n");
        return false;
    }

    mosquitto_subscribe(mosq, nullptr, comms.MQTT_TOPIC_IN.c_str(), 0);
    mosquitto_loop_start(mosq);

    return true;
}

#include <string>
#include <mosquitto.h>
#include "wiringPi.h"

#include "SortingRobot.hh"
#include "Communicator.hh"
#include "config.hh"

bool setup_wiring(SortingRobotSystem *robo) {
    /*******************************************************************************
     * Initial setup wiringPi
     ******************************************************************************/
    wiringPiSetup(); // Regular wiringPi pin mode setup

    // OUTPUT PINS
    pinMode(Config::MOVE_BELT_OUT_PIN, OUTPUT);
    pinMode(Config::MAIN_PUSHER_OUT_PIN, OUTPUT);
    pinMode(Config::WHITE_PUSHER_OUT_PIN, OUTPUT);
    pinMode(Config::BLACK_PUSHER_OUT_PIN, OUTPUT);

    pinMode(Config::STATUS_2_OUT_PIN, OUTPUT);
    pinMode(Config::STATUS_1_OUT_PIN, OUTPUT);
    pinMode(Config::STATUS_0_OUT_PIN, OUTPUT);

    // INPUT PINS
    pinMode(Config::MAIN_PRESENCE_IN_PIN, INPUT);
    pinMode(Config::MAIN_PUSHER_ENDSTOP_IN_PIN, INPUT);
    pinMode(Config::WHITE_SENSOR_IN_PIN, INPUT);
    pinMode(Config::BLACK_SENSOR_IN_PIN, INPUT);
    pinMode(Config::COLOR_SENSOR_0_IN_PIN, INPUT);
    pinMode(Config::COLOR_SENSOR_1_IN_PIN, INPUT);

    // ENSURE ALL PINS TO LOW
    digitalWrite(Config::MOVE_BELT_OUT_PIN, LOW);
    digitalWrite(Config::MAIN_PUSHER_OUT_PIN, LOW);
    digitalWrite(Config::WHITE_PUSHER_OUT_PIN, LOW);
    digitalWrite(Config::BLACK_PUSHER_OUT_PIN, LOW);
    digitalWrite(Config::STATUS_2_OUT_PIN, LOW);
    digitalWrite(Config::STATUS_1_OUT_PIN, LOW);
    digitalWrite(Config::STATUS_0_OUT_PIN, LOW);

    // Initialize pins on components
    robo->whiteActuator.actuator.in.initialise(Config::WHITE_PUSHER_OUT_PIN);
    robo->blackActuator.actuator.in.initialise(Config::BLACK_PUSHER_OUT_PIN);
    robo->wheelMotor.motor.in.initialise(Config::MAIN_PUSHER_OUT_PIN);
    robo->beltMotor.motor.in.initialise(Config::MOVE_BELT_OUT_PIN);

    robo->factorFloorSensor.sensor.in.initialise(Config::MAIN_PRESENCE_IN_PIN);
    robo->wheelStopSensor.sensor.in.initialise(Config::MAIN_PUSHER_ENDSTOP_IN_PIN);
    robo->cs.colourSensor.in.initialise(Config::COLOR_SENSOR_0_IN_PIN, Config::COLOR_SENSOR_1_IN_PIN);
    robo->beltSensorWhite.sensor.in.initialise(Config::WHITE_SENSOR_IN_PIN);
    robo->beltSensorBlack.sensor.in.initialise(Config::BLACK_SENSOR_IN_PIN);

    robo->check_bindings();

    return true;
}

bool setup_mqtt(SortingRobotSystem *robo) {
    mosquitto_lib_init();

    Communicator &comms = Communicator::getInstance();

    // First arg here const char* with ID
    std::string robot_name = "Not Full Nerds";
    mosquitto* mosq = mosquitto_new(robot_name.c_str(), true, nullptr);

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

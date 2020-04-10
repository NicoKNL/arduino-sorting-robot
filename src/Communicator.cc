#include "commutils.hh"

void Communicator::set_mosq(mosquitto * mosq){
    this->mosq = mosq;
};


void Communicator::send_message(std::string message) {
    mosquitto_publish(mosq, nullptr, MQTT_TOPIC_OUT.c_str(), message.length(), message.c_str(), 0, false);
}

void Communicator::heartbeat() {
    if (HEARTBEAT_TRACKER % HEARTBEAT_DELAY == 0) {
        send_message("heartbeat" + std::to_string(OUR_ROBOT_ID));
    }
    ++HEARTBEAT_TRACKER;
}

void Communicator::take_disk() {
    send_message("tookDisk:" + std::to_string(OUR_ROBOT_ID));
}

void Communicator::raise_emergency_stop() {
    send_message("emergencyStop");
}

void Communicator::raise_error() {
    send_message("error:" + std::to_string(OUR_ROBOT_ID));
}

void Communicator::request_disk_counters() {
    send_message("requestDiskCounters");
}

void Communicator::request_disks_taken() {
    requested_disks_taken = true;

    // Reset disk counters as apparently, we have no clueee
    for (int i = 1; i < 5; ++i) {
        DISKS_TAKEN[i] = 0;
    }


    // This method is for recovering. See final paragraph in protocol docs.
    send_message("requestDisksTaken:" + std::to_string(OUR_ROBOT_ID));
}

void Communicator::respond_disks_taken() {
    send_message("respondDisksTaken:" +
            std::to_string(OUR_ROBOT_ID) + "," +
            std::to_string(DISKS_TAKEN[1]) + "," +
            std::to_string(DISKS_TAKEN[2]) + "," +
            std::to_string(DISKS_TAKEN[3]) + "," +
            std::to_string(DISKS_TAKEN[4]));
}

void Communicator::update_external_hearbeats() {
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



void Communicator::destroy_mqtt() {
    mosquitto_disconnect(mosq);
    mosquitto_loop_stop(mosq, true);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
}

void Communicator::handle_message(std::string message) {
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
}

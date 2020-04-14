#include "Communicator.hh"

void Communicator::set_mosq(mosquitto * mosq){
    this->mosq = mosq;
};

void Communicator::set_robot(SortingRobotSystem * robbie_de_robot){
    this->robbie_de_robot = robbie_de_robot;
}

void Communicator::send_message(std::string message) {
    mosquitto_publish(mosq, nullptr, MQTT_TOPIC_OUT.c_str(), message.length(), message.c_str(), 0, false);
}

int Communicator::fairness_balance() {
    int our_count = DISKS_TAKEN[OUR_ROBOT_ID];
    int their_count = 100; // Assume big number to resolve scenario where no other robots on factory floor

    for (int i = 1; i < 5; ++i) {
        if (i == OUR_ROBOT_ID) continue;
        if (!EXTERNAL_ALIVE[i]) continue;
        their_count = std::min(DISKS_TAKEN[i], their_count);
    }

    return our_count - their_count;
}

bool Communicator::is_fair() {
    // Check if we're the only robot alive
    int alive = 0;
    for (int i = 1; i < 5; ++i) {
        if (EXTERNAL_ALIVE[i]) ++alive;
    }

    if (alive <= 1) return true; // Always fair if we're running yolo solo

    // Else check fairness counter by margin
    if (fairness_balance() > FAIRNESS_MARGIN) {
        return false;
    }
    return true;
}

bool Communicator::should_wait() {
    return !is_fair();
}

void Communicator::heartbeat() {
    if (HEARTBEAT_TRACKER % HEARTBEAT_DELAY == 0) {
        send_message("heartbeat" + std::to_string(OUR_ROBOT_ID));
    }
    ++HEARTBEAT_TRACKER;
}

void Communicator::take_disk() {
    std::cout << "[INFO] Sending tookDisk\n";
    ++DISKS_TAKEN[OUR_ROBOT_ID];
    send_message("tookDisk:" + std::to_string(OUR_ROBOT_ID));
}

void Communicator::raise_emergency() {
    std::cout << "[INFO] Sending emergency\n";
    send_message("emergencyStop");
}

void Communicator::raise_error() {
    std::cout << "[INFO] Sending error\n";
    send_message("error:" + std::to_string(OUR_ROBOT_ID));
}

void Communicator::request_disk_counters() {
    std::cout << "[INFO] Sending respondDisksCounters content\n";
    send_message("requestDiskCounters");
}

void Communicator::request_disks_taken() {
    requested_disks_taken = true;

    // Reset disk counters as apparently, we have no clueee
    for (int i = 1; i < 5; ++i) {
        DISKS_TAKEN[i] = 0;
    }

    // This method is for recovering. See final paragraph in protocol docs.
    std::cout << "[INFO] Sending respondDisksTaken content\n";
    send_message("requestDisksTaken:" + std::to_string(OUR_ROBOT_ID));
}

void Communicator::respond_disks_taken() {
    std::cout << "[INFO] Sending respondDisksTaken content\n";
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

// TODO: get disk counter signal?
void Communicator::handle_message(std::string message) {
    if (message.find("heartbeat") == 0) {
        // whose hearbeat is it?
        int external_robot_id = message[9] - '0';
        std::cout << "[INFO] Received heartbeat of robot: " << external_robot_id << "\n";

        // Only keep track of robots that are announced as alive
        if (EXTERNAL_ALIVE[external_robot_id] && external_robot_id != OUR_ROBOT_ID) {
            EXTERNAL_HEARTBEAT_CHECKER[external_robot_id] = 0;
        }
    }
    else if (message.find("start") == 0) {
        std::cout << "[INFO] Received start\n";
        system_stop_requested = false; // Ensure this to remove ambiguity
        system_emergency_stop_requested = false; // Ensure this to remove ambiguity
        system_emergency_stopped = false; // Ensure this to remove ambiguity

        system_start_requested = true;
    }
    else if (message.find("stop") == 0) {
        std::cout << "[INFO] Received stop\n";
        system_start_requested = false; // Ensure this to remove ambiguity
        system_emergency_stop_requested = false; // Ensure this to remove ambiguity
        system_emergency_stopped = false; // Ensure this to remove ambiguity

        system_stop_requested = true;
    }
    else if (message.find("emergencyStop") == 0) {
        std::cout << "[INFO] Received emergencyStop\n";
        system_start_requested = false; // Ensure this to remove ambiguity
        system_stop_requested = false; // Ensure this to remove ambiguity

        system_emergency_stop_requested = true;
    }
    else if (message.find("tookDisk") == 0) {
        int external_robot_id = message[9] - '0';
        std::cout << "[INFO] Received tookDisk of robot: " << external_robot_id << "\n";

        ++DISKS_TAKEN[external_robot_id];
    }
    else if (message.find("requestDisksTaken") == 0) {
        std::cout << "[INFO] Received requestDisksTaken\n";

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
        // If we have sent the request to get the diskTaken from other robots...
        if (requested_disks_taken) {
            //TODO: from this message, fairness can be derived/defined
            std::cout << "[INFO] Received respondDisksTaken\n";

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
    }
}

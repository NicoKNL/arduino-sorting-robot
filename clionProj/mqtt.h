//DBL Embedded Systems, group NotFullNerds
#ifndef SIMPLECLIENT_MQTT_H
#define SIMPLECLIENT_MQTT_H

#include <mosquittopp.h>
#include <cstring>
#include <cstdio>

#define DEFAULT_KEEP_ALIVE 120
#define DEFAULT_MAX_MESSAGE 60

class mqtt_client : public mosqpp::mosquittopp
{
public:
    mqtt_client(const char *id, const char *host, int port);
    ~mqtt_client();

    void on_connect(int rc);
    void on_message(const struct mosquitto_message *message);
    void on_subcribe(int mid, int qos_count, const int *granted_qos);
};

#endif //SIMPLECLIENT_MQTT_H

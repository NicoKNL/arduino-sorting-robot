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
private:
    char m_topic_out[255];
    char m_topic_in[255];
    char m_id[255];
    char m_host[255];
    int m_port;
    // struct mosquitto_message *m_message = new mosquitto_message[3];
    // mosquitto_message * m_messages = new mosquitto_message[1];

public:
    mqtt_client(const char *id, const char *host, int port);
    ~mqtt_client();

    void on_connect(int rc);
    void on_message(const struct mosquitto_message *message);
    void on_subscribe(int mid, int qos_count, const int *granted_qos);
    void check_messages(char *message);
};

#endif //SIMPLECLIENT_MQTT_H
// libmosq_EXPORT int mosquitto_subscribe_simple(
//    	struct 	mosquitto_message 	**	messages,
//    		int 		msg_count,
//    		bool 		want_retained,
//    	const 	char 	*	topic,
//    		int 		qos,
//    	const 	char 	*	host,
//    		int 		port,
//    	const 	char 	*	client_id,
//    		int 		keepalive,
//    		bool 		clean_session,
//    	const 	char 	*	username,
//    	const 	char 	*	password,
//    	const struct 	libmosquitto_will 	*	will,
//    	const struct 	libmosquitto_tls 	*	tls
// )

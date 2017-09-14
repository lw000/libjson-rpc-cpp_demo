/**
 * @file unixdomainsocketserver.cpp
 * @date 11.05.2015
 * @author Alexandre Poirot
 * @brief unixdomainsocketserver.cpp
 */

#include <cstdlib>
#include <iostream>
#include <jsonrpccpp/server.h>
#include <jsonrpccpp/server/connectors/tcpsocketserver.h>
#include <stdio.h>
#include <string>

#include "example.h"

using namespace jsonrpc;

#include <log4z/log4z.h>
using namespace zsummer::log4z;

class SampleServer: public AbstractServer<SampleServer> {
public:
	SampleServer(TcpSocketServer &server) :
			AbstractServer<SampleServer>(server) {
		this->bindAndAddMethod(
				Procedure("sayHello", PARAMS_BY_NAME, JSON_STRING, "name",
						JSON_STRING, NULL), &SampleServer::sayHello);

		this->bindAndAddMethod(
				Procedure("add", PARAMS_BY_NAME, JSON_STRING, "a", JSON_INTEGER,
						"b", JSON_INTEGER, NULL), &SampleServer::add);

		this->bindAndAddMethod(
				Procedure("add_1", PARAMS_BY_NAME, JSON_STRING, "oject",
						JSON_OBJECT,
						NULL), &SampleServer::add_1);

		this->bindAndAddMethod(
				Procedure("sum", PARAMS_BY_NAME, JSON_STRING, "array",
						JSON_ARRAY,
						NULL), &SampleServer::sum);

		this->bindAndAddMethod(
				Procedure("sum_1", PARAMS_BY_NAME, JSON_STRING, "c",
						JSON_ARRAY,
						NULL), &SampleServer::sum_1);

		this->bindAndAddNotification(
				Procedure("notifyServer", PARAMS_BY_NAME, NULL),
				&SampleServer::notifyServer);
	}

	// method
	void sayHello(const Json::Value &request, Json::Value &response) {
		response = "Hello: " + request["name"].asString();
	}

	// method
	void add(const Json::Value &request, Json::Value &response) {
		int a = request["a"].asInt();
		int b = request["b"].asInt();
		response = a + b;
	}

	// method
	void add_1(const Json::Value &request, Json::Value &response) {
		Json::Value ob = request["object"];
		int a = ob["a"].asInt();
		int b = ob["b"].asInt();
		response = a + b;
		response = 10;
	}

	// method
	void sum(const Json::Value &request, Json::Value &response) {
		Json::Value ar = request["array"];
		int c = 0;
		for (int i = 0; i < ar.size(); i++) {
			c += ar[i].asInt();
		}
		response = c;
	}

	// method
		void sum_1(const Json::Value &request, Json::Value &response) {
			int c = request["c"].asInt();
			for (int i = 0; i < c; i++) {
				c += i;
			}
			response = c;
		}

	// notification
	void notifyServer(const Json::Value &request) {
		(void) request;
		std::cout << "server received some Notification" << std::endl;
	}
};

int tcpsocketserver(int argc, char **argv) {
	try {
		std::string ip;
		unsigned int port;

		if (argc == 3) {
			ip = std::string(argv[1]);
			port = atoi(argv[2]);
		} else {
			ip = "127.0.0.1";
			port = 6543;
		}

		std::cout << "Params are :" << std::endl;
		std::cout << "\t ip: " << ip << std::endl;
		std::cout << "\t port: " << port << std::endl;

		TcpSocketServer server(ip, port);
		SampleServer serv(server);
		if (serv.StartListening()) {
			std::cout << "Server started successfully" << std::endl;
			getchar();
			serv.StopListening();
		} else {
			std::cout << "Error starting Server" << std::endl;
		}

	} catch (jsonrpc::JsonRpcException &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}

/**
 * @file tcpsocketclient.cpp
 * @date 17.07.2015
 * @author Alexandre Poirot <alexandre.poirot@legrand.fr>
 * @brief tcpsocketclient.cpp
 */

#include <cstdlib>
#include <iostream>
#include <jsonrpccpp/client.h>
#include <jsonrpccpp/client/connectors/tcpsocketclient.h>

#include "example.h"

using namespace jsonrpc;

#include <log4z/log4z.h>
using namespace zsummer::log4z;

int tcpsocketclient(int argc, char **argv) {
	std::string host;
	unsigned int port;

	if (argc == 3) {
		host = std::string(argv[1]);
		port = atoi(argv[2]);
	} else {
		host = "127.0.0.1";
		port = 6543;
	}

	std::cout << "Params are :" << std::endl;
	std::cout << "\t host: " << host << std::endl;
	std::cout << "\t port: " << port << std::endl;

	TcpSocketClient client(host, port);
	Client cli(client);

	try {

		{
			Json::Value params;
			params["name"] = "Peter";
			std::string c = cli.CallMethod("sayHello", params).asString();
			LOGFMTD("method: %s, result: %s", "sayHello", c.c_str());
		}

		{
			Json::Value params;
			params["a"] = 1;
			params["b"] = 2;
			int c = cli.CallMethod("add", params).asInt();
			LOGFMTD("method: %s, result: %d", "add", c);
		}

//		{
//			Json::Value params;
//			{
//				params["a"] = 1;
//				params["b"] = 2;
//			}
//			Json::FastWriter writer;
//			std::string s = writer.write(params);
//			int c = cli.CallMethod("add_1", params).asInt();
//			LOGFMTD("method: %s, result: %d", "add_1", c);
//		}

		{
			Json::Value params;
			{
				Json::Value o;
				for (int i = 0; i < 1000; i++) {
					o[i] = i;
				}
				params["array"] = o;
			}
			int c = cli.CallMethod("sum", params).asInt();
			LOGFMTD("method: %s, result: %d", "sum", c);
		}

		clock_t t = clock();

		for (int i = 0; i < 10000; i++) {
			Json::Value params;
			{
				Json::Value o;
				for (int i = 0; i < 1000; i++) {
					o[i] = i;
				}
				params["array"] = o;
			}
			int c = cli.CallMethod("sum", params).asInt();
			//				LOGFMTD("method: %s, result: %d", "sum", c);
		}

		clock_t t1 = clock();
		LOGFMTA("all exec times: %f", ((double)t1-t)/CLOCKS_PER_SEC);

	} catch (JsonRpcException &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}

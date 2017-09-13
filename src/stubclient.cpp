/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    stubclient.cpp
 * @date    01.05.2013
 * @author  Peter Spiess-Knafl <dev@spiessknafl.at>
 * @license See attached LICENSE.txt
 ************************************************************************/

#include <iostream>

#include "example.h"
#include "stubclient.h"

#include <jsonrpccpp/client/connectors/httpclient.h>

using namespace jsonrpc;

int stubclient(int argc, char **argv) {

	Json::Value a = 3;
	Json::Value b = "3";

	std::map<Json::Value, Json::Value> responses;

	responses[a] = b;
	responses[b] = "asölfj";

	std::cout << responses[b] << std::endl;

	if (a == b) {
		std::cout << a.toStyledString() << " == " << b.toStyledString() << std::endl;
	} else {
		std::cout << a.toStyledString() << " != " << b.toStyledString() << std::endl;
	}

	HttpClient httpclient("http://localhost:8383");
	// StubClient c(httpclient, JSONRPC_CLIENT_V1); //json-rpc 1.0
	StubClient c(httpclient, JSONRPC_CLIENT_V2); // json-rpc 2.0

	try {
		std::cout << c.sayHello("Peter Knafl") << std::endl;
		c.notifyServer();

		std::cout << " 3 + 5 = " << c.addNumbers(3, 5) << std::endl;
		std::cout << " 3.2 + 5.3 = " << c.addNumbers2(3.2, 5.3) << std::endl;
		std::cout << "Compare: " << c.isEqual("Peter", "peter") << std::endl;
		std::cout << "Build object: " << c.buildObject("Peter", 1990) << std::endl;

	} catch (JsonRpcException &e) {
		std::cerr << e.what() << std::endl;
	}
}

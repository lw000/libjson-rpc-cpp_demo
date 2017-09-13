/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    stubserver.cpp
 * @date    02.05.2013
 * @author  Peter Spiess-Knafl <dev@spiessknafl.at>
 * @license See attached LICENSE.txt
 ************************************************************************/
#include <iostream>

#include <jsonrpccpp/server/connectors/httpserver.h>
#include <stdio.h>

#include "abstractstubserver.h"

using namespace jsonrpc;

class MyStubServer: public AbstractStubServer {
public:
	MyStubServer(AbstractServerConnector &connector, serverVersion_t type);

	virtual void notifyServer();
	virtual std::string sayHello(const std::string &name);
	virtual int addNumbers(int param1, int param2);
	virtual double addNumbers2(double param1, double param2);
	virtual bool isEqual(const std::string &str1, const std::string &str2);
	virtual Json::Value buildObject(const std::string &name, int age);
	virtual std::string methodWithoutParameters();
};

MyStubServer::MyStubServer(AbstractServerConnector &connector,
		serverVersion_t type) :
		AbstractStubServer(connector, type) {
}

void MyStubServer::notifyServer() {
	std::cout << "Server got notified" << std::endl;
}

std::string MyStubServer::sayHello(const std::string &name) {
	return "Hello " + name;
}

int MyStubServer::addNumbers(int param1, int param2) {
	return param1 + param2;
}

double MyStubServer::addNumbers2(double param1, double param2) {
	return param1 + param2;
}

bool MyStubServer::isEqual(const std::string &str1, const std::string &str2) {
	return str1 == str2;
}

Json::Value MyStubServer::buildObject(const std::string &name, int age) {
	Json::Value result;
	result["name"] = name;
	result["year"] = age;
	return result;
}

std::string MyStubServer::methodWithoutParameters() {
	return "Test";
}

int stubserver(int argc, char **argv) {
	HttpServer httpserver(8383);
	MyStubServer s(httpserver, JSONRPC_SERVER_V1V2);
	try {
		if (s.StartListening()) {
			std::cout << "Hit enter to stop the server" << std::endl;

			getchar();

			s.StopListening();
		} else {

		}
	} catch (jsonrpc::JsonRpcException &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}

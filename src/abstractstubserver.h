/**
 * This file is generated by jsonrpcstub, DO NOT CHANGE IT MANUALLY!
 */

#ifndef JSONRPC_CPP_STUB_ABSTRACTSTUBSERVER_H_
#define JSONRPC_CPP_STUB_ABSTRACTSTUBSERVER_H_

#include <jsonrpccpp/server.h>

class AbstractStubServer: public jsonrpc::AbstractServer<AbstractStubServer> {
public:
	AbstractStubServer(jsonrpc::AbstractServerConnector &conn,
			jsonrpc::serverVersion_t type = jsonrpc::JSONRPC_SERVER_V2) :
			jsonrpc::AbstractServer<AbstractStubServer>(conn, type) {
		this->bindAndAddMethod(
				jsonrpc::Procedure("sayHello", jsonrpc::PARAMS_BY_NAME,
						jsonrpc::JSON_STRING, "name", jsonrpc::JSON_STRING,
						NULL), &AbstractStubServer::sayHelloI);
		this->bindAndAddNotification(
				jsonrpc::Procedure("notifyServer", jsonrpc::PARAMS_BY_NAME,
				NULL), &AbstractStubServer::notifyServerI);
		this->bindAndAddMethod(
				jsonrpc::Procedure("addNumbers", jsonrpc::PARAMS_BY_POSITION,
						jsonrpc::JSON_INTEGER, "param01", jsonrpc::JSON_INTEGER,
						"param02", jsonrpc::JSON_INTEGER, NULL),
				&AbstractStubServer::addNumbersI);
		this->bindAndAddMethod(
				jsonrpc::Procedure("addNumbers2", jsonrpc::PARAMS_BY_POSITION,
						jsonrpc::JSON_REAL, "param01", jsonrpc::JSON_REAL,
						"param02", jsonrpc::JSON_REAL, NULL),
				&AbstractStubServer::addNumbers2I);
		this->bindAndAddMethod(
				jsonrpc::Procedure("isEqual", jsonrpc::PARAMS_BY_POSITION,
						jsonrpc::JSON_BOOLEAN, "param01", jsonrpc::JSON_STRING,
						"param02", jsonrpc::JSON_STRING, NULL),
				&AbstractStubServer::isEqualI);
		this->bindAndAddMethod(
				jsonrpc::Procedure("buildObject", jsonrpc::PARAMS_BY_POSITION,
						jsonrpc::JSON_OBJECT, "param01", jsonrpc::JSON_STRING,
						"param02", jsonrpc::JSON_INTEGER, NULL),
				&AbstractStubServer::buildObjectI);
		this->bindAndAddMethod(
				jsonrpc::Procedure("methodWithoutParameters",
						jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_STRING, NULL),
				&AbstractStubServer::methodWithoutParametersI);
	}

	inline virtual void sayHelloI(const Json::Value &request,
			Json::Value &response) {
		response = this->sayHello(request["name"].asString());
	}

	inline virtual void notifyServerI(const Json::Value &request) {
		(void) request;
		this->notifyServer();
	}

	inline virtual void addNumbersI(const Json::Value &request,
			Json::Value &response) {
		response = this->addNumbers(request[0u].asInt(), request[1u].asInt());
	}

	inline virtual void addNumbers2I(const Json::Value &request,
			Json::Value &response) {
		response = this->addNumbers2(request[0u].asDouble(),
				request[1u].asDouble());
	}

	inline virtual void isEqualI(const Json::Value &request,
			Json::Value &response) {
		response = this->isEqual(request[0u].asString(),
				request[1u].asString());
	}

	inline virtual void buildObjectI(const Json::Value &request,
			Json::Value &response) {
		response = this->buildObject(request[0u].asString(),
				request[1u].asInt());
	}

	inline virtual void methodWithoutParametersI(const Json::Value &request,
			Json::Value &response) {
		(void) request;
		response = this->methodWithoutParameters();
	}

	virtual std::string sayHello(const std::string& name) = 0;
	virtual void notifyServer() = 0;
	virtual int addNumbers(int param01, int param02) = 0;
	virtual double addNumbers2(double param01, double param02) = 0;
	virtual bool isEqual(const std::string& param01,
			const std::string& param02) = 0;
	virtual Json::Value buildObject(const std::string& param01,
			int param02) = 0;
	virtual std::string methodWithoutParameters() = 0;
};

#endif //JSONRPC_CPP_STUB_ABSTRACTSTUBSERVER_H_
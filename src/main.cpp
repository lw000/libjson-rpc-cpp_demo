//============================================================================
// Name        : jsoncpp_rpc_cpp_demo.cpp
// Author      : lw
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <string>

#include "example.h"

#include <log4z/log4z.h>
using namespace zsummer::log4z;

int main(int argc, char **argv) {

	ILog4zManager::getInstance()->start();

	std::string s(argv[1]);

	if (s.compare("s") == 0) {
		tcpsocketserver(argc, argv);
	} else 	if (s.compare("c") == 0) {
		tcpsocketclient(argc, argv);
	} else {
		printf ("error. \n");
	}

	return 0;
}

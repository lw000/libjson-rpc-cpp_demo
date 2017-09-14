//============================================================================
// Name        : jsoncpp_rpc_cpp_demo.cpp
// Author      : lw
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <string>

#include "example.h"
#include <getopt.h>

#include <log4z/log4z.h>
using namespace zsummer::log4z;

int main(int argc, char **argv) {

	if (argc < 2) {
			printf("client please input (-t s) or (-t c). \n");
			return 0;
		}

		std::string t;

		int ch = 0;
		while ((ch = getopt(argc, argv, "t:")) != -1) {
			switch (ch) {
			case 't': {
				if (optarg != NULL) {
					t = optarg;
				}
				break;
			}
			default: {
				fprintf(stderr, "(-t s) or (-t c)\n");
				exit(1);
				break;
			}
			}
		}

	ILog4zManager::getInstance()->start();


	if (t.compare("s") == 0) {
		tcpsocketserver(argc, argv);
	} else if (t.compare("c") == 0) {
		tcpsocketclient(argc, argv);
	} else {
		printf("error. \n");
	}

	return 0;
}

#pragma once

#ifdef _WIN32
	#include "Proto/Net/IP/TCP/Server/Windows/MultithreadedServer.h"
#elifdef __unix__
	#include "Proto/Net/IP/TCP/Server/Unix/MultithreadedServer.h"
#endif
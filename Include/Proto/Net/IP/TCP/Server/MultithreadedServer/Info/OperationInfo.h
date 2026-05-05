#pragma once

#ifdef _WIN32
	#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Windows/OperationInfo.h"
#elifdef __unix__
	#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Unix/OperationInfo.h"
#endif
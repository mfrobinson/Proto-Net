#pragma once

#ifdef _WIN32
	#include "Proto/Net/IP/TCP/Windows/ServerSocket.h"
#elifdef __unix__
	#include "Proto/Net/IP/TCP/Linux/ServerSocket.h"
#endif
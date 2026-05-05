#pragma once

#ifdef _WIN32
	#include "Proto/Net/IP/TCP/Windows/ClientSocket.h"
#elifdef __unix__
	#include "Proto/Net/IP/TCP/Linux/ClientSocket.h"
#endif
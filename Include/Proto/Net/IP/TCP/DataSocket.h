#pragma once

#ifdef _WIN32
	#include "Proto/Net/IP/TCP/Windows/DataSocket.h"
#elifdef __unix__
	#include "Proto/Net/IP/TCP/Linux/DataSocket.h"
#endif
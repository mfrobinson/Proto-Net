#pragma once
#include "Proto/Platform.h"

#ifdef WINDOWS_PLATFORM
	#include "Proto/Net/IP/TCP/Windows/DataSocket.h"
#elifdef LINUX_PLATFORM
	#include "Proto/Net/IP/TCP/Linux/DataSocket.h"
#endif
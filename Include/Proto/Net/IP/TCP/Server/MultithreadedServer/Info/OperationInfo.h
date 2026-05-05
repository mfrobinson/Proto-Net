#pragma once
#include "Proto/Platform.h"

#ifdef WINDOWS_PLATFORM
	#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Windows/OperationInfo.h"
#elifdef LINUX_PLATFORM
	#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Linux/OperationInfo.h"
#endif
#pragma once
#include "Proto/Platform.h"

#ifdef WINDOWS_PLATFORM
	#include "Proto/Net/Windows/Socket.h"
#elifdef LINUX_PLATFORM
	#include "Proto/Net/Linux/Socket.h"
#endif
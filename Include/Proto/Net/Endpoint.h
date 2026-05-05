#pragma once
#include "Proto/Platform.h"

#ifdef WINDOWS_PLATFORM
	#include "Proto/Net/Windows/Endpoint.h"
#elifdef LINUX_PLATFORM
	#include "Proto/Net/Linux/Endpoint.h"
#endif
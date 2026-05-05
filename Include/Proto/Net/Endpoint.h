#pragma once
#include "Proto/Platform.h"

#ifdef _WIN32
	#include "Proto/Net/Windows/Endpoint.h"
#elifdef __unix__
	#include "Proto/Net/Linux/Endpoint.h"
#endif
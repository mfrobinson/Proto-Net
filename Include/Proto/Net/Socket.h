#pragma once

#ifdef _WIN32
	#include "Proto/Net/Windows/Socket.h"
#elifdef __unix__
	#include "Proto/Net/Linux/Socket.h"
#endif
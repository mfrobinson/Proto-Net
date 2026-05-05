#pragma once
#include "Proto/Platform.h"

#ifdef __WIN32
	#include "Proto/Net/Windows/Socket.h"
#elifdef __unix__
	#include "Proto/Net/Linux/Socket.h"
#endif
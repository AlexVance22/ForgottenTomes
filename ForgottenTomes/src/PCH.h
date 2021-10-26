#pragma once

#include <filesystem>
#include <algorithm>
#include <optional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#ifdef FTOMES_PLATFORM_WINDOWS
	#include <windows.h>
#endif

#include <json.hpp>
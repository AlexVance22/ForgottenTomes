#pragma once

#include <filesystem>
#include <algorithm>
#include <exception>
#include <optional>
#include <chrono>

#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <string>
#include <array>

#include <cstdlib>
#include <cmath>

#ifdef LTOMES_PLATFORM_WINDOWS
	#include <windows.h>
#endif

#include <json.hpp>

namespace fs = std::filesystem;
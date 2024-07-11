#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <fstream>
#include <array>
#include <vector>
#include <queue>
#include <mutex>
#include <future>
#include <shared_mutex>
#include <unordered_map>
#include <unordered_set>

#include "Core/Core.h"
#include "Core/Log.h"
#include "Core/Timestep.h"

#include <glm/glm.hpp>

#ifdef MC_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
#pragma once

#include <iostream>
#include <cstdint>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Like/Core/Log.h"

#include "Like/Debug/Instrumentor.h"

#if defined(LK_PLATFORM_WINDOWS)
    #include <Windows.h>
#endif
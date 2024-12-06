#pragma once

#ifdef LK_PLATFORM_WINDOWS
	#ifdef LK_BUILD_DLL
		#define LIKE_API __declspec(dllexport)
	#else
		#define LIKE_API __declspec(dllimport)
	#endif
#else
	#error Like only support Windows!
#endif

#ifdef LK_ENABLE_ASSERTS
#define LK_ASSERT(x, ...) { if(!(x)) {LK_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define LK_CORE_ASSERT(x, ...) { if(!(x)) {LK_FATAL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define LK_ASSERT(x, ...)
	#define LK_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
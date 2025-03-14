#pragma once

#include <memory>

#ifdef LK_PLATFORM_WINDOWS
#if LK_DYNAMIC_LINK
	#ifdef LK_BUILD_DLL
		#define LIKE_API __declspec(dllexport)
	#else
		#define LIKE_API __declspec(dllimport)
	#endif
#else
	#define LIKE_API
#endif
#else
	#error Like only support Windows!
#endif

#ifdef LK_DEBUG
	#define LK_ENABLE_ASSERTS
#endif

#ifdef LK_ENABLE_ASSERTS
#define LK_ASSERT(x, ...) { if(!(x)) {LK_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define LK_CORE_ASSERT(x, ...) { if(!(x)) {LK_FATAL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define LK_ASSERT(x, ...)
	#define LK_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define LK_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Like
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}
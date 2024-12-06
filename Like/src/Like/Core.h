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

#define BIT(x) (1 << x)
#pragma once
#include "Log.h"

extern Like::Application* Like::CreateApplication();

#ifdef LK_PLATFORM_WINDOWS
	int main(int argc, char** argv) {
		Like::Log::Init();

		LK_PROFILE_BEGIN_SESSION("Startup", "LikeProfile-Startup.json");
		auto app = Like::CreateApplication();
		LK_PROFILE_END_SESSION();
		
		LK_PROFILE_BEGIN_SESSION("Runtime", "LikeProfile-Runtime.json");
		app->Run();
		LK_PROFILE_END_SESSION();
		
		LK_PROFILE_BEGIN_SESSION("Shutdown", "LikeProfile-Shutdown.json");
		delete app;
		LK_PROFILE_END_SESSION();
		
		return 0;
	}
#endif
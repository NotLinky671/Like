#pragma once
#include "Log.h"

extern Like::Application* Like::CreateApplication();

#ifdef LK_PLATFORM_WINDOWS
	int main(int argc, char** argv) {
		Like::Log::Init();

		auto app = Like::CreateApplication();
		app->Run();
		delete app;
		return 0;
	}
#endif
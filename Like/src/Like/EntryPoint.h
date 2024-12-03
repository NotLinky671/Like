#pragma once

extern Like::Application* Like::CreateApplication();

#ifdef LK_PLATFORM_WINDOWS
	int main(int argc, char** argv) {
		auto app = Like::CreateApplication();
		app->Run();
		delete app;
		return 0;
	}
#endif
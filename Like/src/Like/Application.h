#pragma once

#include "Core.h"

namespace Like {
	class LIKE_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be define in client
	Application* CreateApplication();
}

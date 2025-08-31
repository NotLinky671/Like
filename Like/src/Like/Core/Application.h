#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Like/Events/Event.h"
#include "Like/Events/ApplicationEvent.h"

#include "Like/Core/Timestep.h"

#include "Like/ImGui/ImGuiLayer.h"

namespace Like {
	class LIKE_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		static Application* s_Instance;
		Timestep m_Timestep;
		float m_LastFrameTime = 0.0f;
	};

	// To be define in client
	Application* CreateApplication();
}

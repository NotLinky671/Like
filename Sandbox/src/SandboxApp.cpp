#include <Like.h>

#include "imgui/imgui.h"

class ExampleLayer : public Like::Layer {
public:
	ExampleLayer() : Layer("Example"){}

	void OnUpdate() override {
		if (Like::Input::IsKeyPressed(LK_KEY_TAB))
		{
			LK_TRACE("Tab key is pressed (poll)!");
		}
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	void OnEvent(Like::Event& event) override {
		if (event.GetEventType() == Like::EventType::KeyPressed)
		{
			Like::KeyPressedEvent& e = (Like::KeyPressedEvent&)event;
			if (e.GetKeyCode() == LK_KEY_TAB)
				LK_TRACE("Tab key is pressed (event)!");
			LK_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Like::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

Like::Application* Like::CreateApplication() {
	return new Sandbox();
}
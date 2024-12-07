#include <Like.h>

class ExampleLayer : public Like::Layer {
public:
	ExampleLayer() : Layer("Example"){}

	void OnUpdate() override {
		LK_INFO("ExampleLayer::OnUpdate");
	}

	void OnEvent(Like::Event& event) override {
		LK_TRACE(("{0}", event));
	}
};

class Sandbox : public Like::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Like::ImGuiLayer());
	}

	~Sandbox() {

	}
};

Like::Application* Like::CreateApplication() {
	return new Sandbox();
}
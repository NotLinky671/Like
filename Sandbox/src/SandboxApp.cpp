#include <Like.h>

class Sandbox : public Like::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Like::Application* Like::CreateApplication() {
	return new Sandbox();
}
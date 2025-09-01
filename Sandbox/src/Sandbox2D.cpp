#include "Sandbox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"),
      m_CameraController(1280.0f / 720.0f)
{
	
}

void Sandbox2D::OnAttach()
{
	
}

void Sandbox2D::OnDetach()
{
    
}

void Sandbox2D::OnUpdate(Like::Timestep ts)
{
    // Update
    m_CameraController.OnUpdate(ts);

    // Render
	Like::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Like::RenderCommand::Clear();

	Like::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Like::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f}, {0.8f, 0.2f, 0.3f, 1.0f});
	Like::Renderer2D::EndScene();
	
	// std::dynamic_pointer_cast<Like::OpenGLShader>(m_FlatColorShader)->Bind();
	// std::dynamic_pointer_cast<Like::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(Like::Event& e)
{
    m_CameraController.OnEvent(e);
}

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
	m_SquareVA = Like::VertexArray::Create();

	float squareVertices[5 * 4] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
		
	Like::Ref<Like::VertexBuffer> squareVB;
	squareVB.reset(Like::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout
	(
	{
		{ Like::ShaderDataType::Float3, "a_Position" }
		}
	);
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Like::Ref<Like::IndexBuffer> squareIB;
	squareIB.reset(Like::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = Like::Shader::Create("assets/shaders/FlatColor.glsl");
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

	Like::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Like::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Like::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
	
	Like::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Like::Renderer::EndScene();
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

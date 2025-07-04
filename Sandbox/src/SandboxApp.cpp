#include <Like.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

class ExampleLayer : public Like::Layer {
public:
	ExampleLayer()
		: Layer("Example"),
		  m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		m_VertexArray.reset(Like::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Like::Ref<Like::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Like::VertexBuffer::Create(vertices, sizeof(vertices)));
		
		Like::BufferLayout layout = {
			{ Like::ShaderDataType::Float3, "a_Position" },
			{ Like::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Like::Ref<Like::IndexBuffer> indexBuffer;
		indexBuffer.reset(Like::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Like::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Like::Ref<Like::VertexBuffer> squareVB;
		squareVB.reset(Like::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Like::ShaderDataType::Float3, "a_Position" },
			{ Like::ShaderDataType::Float2, "a_TexCoord" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Like::Ref<Like::IndexBuffer> squareIB;
		squareIB.reset(Like::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 m_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = m_Position + 0.5f;
				gl_Position = u_ViewProjection * u_Transform * vec4(m_Position, 1.0f);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			out vec4 FragColor;

			in vec3 v_Position;

			void main()
			{
				FragColor = vec4(v_Position * 0.5f + 0.5f, 1.0f);
			}
		)";
		
		m_Shader = Like::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = Like::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Like::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = Like::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Like::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Like::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Like::Timestep ts) override
	{
		// LK_TRACE("Delta-Time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());
		
		if (Like::Input::IsKeyPressed(LK_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Like::Input::IsKeyPressed(LK_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		
		if (Like::Input::IsKeyPressed(LK_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Like::Input::IsKeyPressed(LK_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Like::Input::IsKeyPressed(LK_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Like::Input::IsKeyPressed(LK_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		
		Like::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Like::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Like::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Like::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Like::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);
		
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Like::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Like::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_ChernoLogoTexture->Bind();
		Like::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));


		// Triangle
		// Like::Renderer::Submit(m_Shader, m_VertexArray);

		Like::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Like::Event& event) override
	{
		
	}
private:
	Like::ShaderLibrary m_ShaderLibrary;
	Like::Ref<Like::Shader> m_Shader;
	Like::Ref<Like::VertexArray> m_VertexArray;

	Like::Ref<Like::Shader> m_FlatColorShader;
	Like::Ref<Like::VertexArray> m_SquareVA;
	
	Like::Ref<Like::Texture2D> m_Texture;
	Like::Ref<Like::Texture2D> m_ChernoLogoTexture;
	
	Like::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 20.0f;
	float m_CameraMoveSpeed = 4.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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
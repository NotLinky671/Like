#include <Like.h>

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

		std::shared_ptr<Like::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Like::VertexBuffer::Create(vertices, sizeof(vertices)));
		
		Like::BufferLayout layout = {
			{ Like::ShaderDataType::Float3, "a_Position" },
			{ Like::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Like::IndexBuffer> indexBuffer;
		indexBuffer.reset(Like::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Like::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};
		std::shared_ptr<Like::VertexBuffer> squareVB;
		squareVB.reset(Like::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Like::ShaderDataType::Float3, "a_Position" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Like::IndexBuffer> squareIB;
		squareIB.reset(Like::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 m_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = m_Position + 0.5f;
				gl_Position = u_ViewProjection * vec4(m_Position, 1.0f);
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
		
		m_Shader.reset(new Like::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Like::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate() override
	{
		if (Like::Input::IsKeyPressed(LK_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed;
		else if (Like::Input::IsKeyPressed(LK_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed;
		
		if (Like::Input::IsKeyPressed(LK_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed;
		else if (Like::Input::IsKeyPressed(LK_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed;

		if (Like::Input::IsKeyPressed(LK_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed;
		if (Like::Input::IsKeyPressed(LK_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed;
		
		Like::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Like::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Like::Renderer::BeginScene(m_Camera);
			
		Like::Renderer::Submit(m_SquareVA, m_BlueShader);
		Like::Renderer::Submit(m_VertexArray, m_Shader);

		Like::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		
	}

	void OnEvent(Like::Event& event) override
	{
		
	}
private:
	std::shared_ptr<Like::Shader> m_Shader;
	std::shared_ptr<Like::VertexArray> m_VertexArray;

	std::shared_ptr<Like::VertexArray> m_SquareVA;
	std::shared_ptr<Like::Shader> m_BlueShader;

	Like::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 1.0f;
	float m_CameraMoveSpeed = 0.1f;
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
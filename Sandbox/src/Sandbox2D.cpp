#include "Sandbox2D.h"

#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"),
      m_CameraController(1280.0f / 720.0f) {
}

void Sandbox2D::OnAttach() {
    LK_PROFILE_FUNCTION()

    m_CheckerboardTexture = Like::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach() {
    LK_PROFILE_FUNCTION()
}

void Sandbox2D::OnUpdate(Like::Timestep ts) {
    LK_PROFILE_FUNCTION()

    // Update
    m_CameraController.OnUpdate(ts);

    // Render
    {
        LK_PROFILE_SCOPE("Renderer Prep")
        Like::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Like::RenderCommand::Clear();
    }

    {
        LK_PROFILE_SCOPE("Renderer Draw")
        Like::Renderer2D::BeginScene(m_CameraController.GetCamera());
        Like::Renderer2D::DrawRotatedQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, glm::radians(45.0f), {0.8f, 0.2f, 0.3f, 1.0f});
        Like::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, m_SquareColor);
        Like::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {10.0f, 10.0f},
                                   m_CheckerboardTexture, 10.0f);
        Like::Renderer2D::EndScene();
    }
}

void Sandbox2D::OnImGuiRender() {
    LK_PROFILE_FUNCTION()

    ImGui::Begin("Settings");

    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

    ImGui::End();
}

void Sandbox2D::OnEvent(Like::Event& e) {
    m_CameraController.OnEvent(e);
}

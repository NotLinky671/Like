#pragma once

#include "Like.h"

class Sandbox2D : public Like::Layer
{
public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;
    
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    
    virtual void OnUpdate(Like::Timestep ts) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Like::Event& e) override;
private:
    Like::OrthographicCameraController m_CameraController;
    
    Like::Ref<Like::VertexArray> m_SquareVA;
    Like::Ref<Like::Shader> m_FlatColorShader;

    Like::Ref<Like::Texture2D> m_CheckerboardTexture;

    struct ProfileResult
    {
        const char* Name;
        float Time;
    };

    std::vector<ProfileResult> m_ProfileResults;

    glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};

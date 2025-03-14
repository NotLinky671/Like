#pragma once

#include "Like/Renderer/RendererAPI.h"

namespace Like
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void Init() override;
        
        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void Clear() override;

        virtual void DrawIndex(const Ref<VertexArray>& vertexArray) override;
    };
}
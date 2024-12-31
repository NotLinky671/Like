#pragma once

#include "Like/Renderer/RendererAPI.h"

namespace Like
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void Clear() override;

        virtual void DrawIndex(const std::shared_ptr<VertexArray>& vertexArray) override;
    };
}
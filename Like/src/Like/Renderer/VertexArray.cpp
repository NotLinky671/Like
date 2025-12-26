#include "lkpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Like
{
    Ref<VertexArray> VertexArray::Create()
    {
        LK_CORE_INFO("VertexArray::Create() starting");
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:    LK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:  LK_CORE_INFO("Creating OpenGLVertexArray"); return std::make_shared<OpenGLVertexArray>();
        }

        LK_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}

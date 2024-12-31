#include "lkpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Like
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}
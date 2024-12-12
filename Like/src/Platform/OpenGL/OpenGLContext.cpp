#include "lkpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Like
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {
        LK_CORE_ASSERT(m_WindowHandle, "Window handle is null");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        LK_CORE_ASSERT(status, "Failed to initialize glad!");

        LK_CORE_INFO("OpenGL Info: ");
        LK_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
        LK_CORE_INFO("  Renderer: {0}" , glGetString(GL_RENDERER));
        LK_CORE_INFO("  Version: {0}" , glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}

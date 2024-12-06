#include "lkpch.h"
#include "WindowsWindow.h"

#include "Like/Log.h"

namespace Like {
    static bool s_GLFWInitialized = false;
    
    Window* Window::Create(const WindowProps& props) {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props) {
        Init(props);
    }

    WindowsWindow::~WindowsWindow() {
        Shutdown();
    }

    void WindowsWindow::Init(const WindowProps& props) {
        m_Data.m_Title = props.Title;
        m_Data.m_Width = props.Width;
        m_Data.m_Height = props.Height;

        LK_CORE_INFO("Creating window {0} {1} {2}", props.Title, props.Width, props.Height);

        if (!s_GLFWInitialized) {
            int success = glfwInit();
            LK_CORE_ASSERT(success, "Could not initialize GLFW!");
            s_GLFWInitialized = true;
        }

        m_window = glfwCreateWindow((int)m_Data.m_Width, (int)m_Data.m_Height, m_Data.m_Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_window);
        glfwSetWindowUserPointer(m_window, &m_Data);
        SetVSync(true);
    }

    void WindowsWindow::Shutdown() {
        glfwDestroyWindow(m_window);
    }

    void WindowsWindow::OnUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    void WindowsWindow::SetVSync(bool enabled) {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.m_VSync = enabled;
    }

    bool WindowsWindow::IsVSync() const {
        return m_Data.m_VSync;
    }
}

#pragma once

#include "Like/Window.h"

#include <GLFW/glfw3.h>

namespace Like {
    class LIKE_API WindowsWindow : public Window {
    public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return m_Data.m_Width; }
        inline unsigned int GetHeight() const override { return m_Data.m_Height; }

        inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.m_EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

    private:
        GLFWwindow* m_window;
        
        struct WindowData {
          std::string m_Title;
          unsigned int m_Width;
          unsigned int m_Height;
          bool m_VSync;

          EventCallbackFn m_EventCallback;
        };

        WindowData m_Data;
    };
}

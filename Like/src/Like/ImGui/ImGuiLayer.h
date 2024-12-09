#pragma once
#include "Events/ApplicationEvent.h"
#include "Like/Layer.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace Like {
    class LIKE_API ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();
    private:
        float m_Time = 0.0f;
    };
}

project(Like
        LANGUAGES CXX
)

add_library(Like STATIC)

target_sources(Like
        PRIVATE
        src/Like/Core/Application.cpp
        src/Like/Core/Layer.cpp
        src/Like/Core/LayerStack.cpp
        src/Like/Core/Log.cpp
        src/Like/ImGui/ImGuiBuild.cpp
        src/Like/ImGui/ImGuiLayer.cpp
        src/Like/Renderer/Buffer.cpp
        src/Like/Renderer/OrthographicCamera.cpp
        src/Like/Renderer/OrthographicCameraController.cpp
        src/Like/Renderer/RenderCommand.cpp
        src/Like/Renderer/Renderer.cpp
        src/Like/Renderer/Renderer2D.cpp
        src/Like/Renderer/RendererAPI.cpp
        src/Like/Renderer/Shader.cpp
        src/Like/Renderer/Texture.cpp
        src/Like/Renderer/VertexArray.cpp
        src/Platform/OpenGL/OpenGLBuffer.cpp
        src/Platform/OpenGL/OpenGLContext.cpp
        src/Platform/OpenGL/OpenGLRendererAPI.cpp
        src/Platform/OpenGL/OpenGLShader.cpp
        src/Platform/OpenGL/OpenGLTexture.cpp
        src/Platform/OpenGL/OpenGLVertexArray.cpp
        src/Platform/Windows/WindowsInput.cpp
        src/Platform/Windows/WindowsWindow.cpp
        vendor/stb_image/stb_image.cpp
        vendor/imgui/imgui.cpp
        vendor/imgui/imgui_demo.cpp
        vendor/imgui/imgui_draw.cpp
        vendor/imgui/imgui_tables.cpp
        vendor/imgui/imgui_widgets.cpp

        PUBLIC
        FILE_SET HEADERS
        FILES
        src/Like/Core/Application.h
        src/Like/Core/Core.h
        src/Like/Core/EntryPoint.h
        src/Like/Core/Input.h
        src/Like/Core/KeyCodes.h
        src/Like/Core/Layer.h
        src/Like/Core/LayerStack.h
        src/Like/Core/Log.h
        src/Like/Core/MouseButtonCodes.h
        src/Like/Core/Timestep.h
        src/Like/Core/Window.h
        src/Like/Debug/Instrumentor.h
        src/Like/Events/ApplicationEvent.h
        src/Like/Events/Event.h
        src/Like/Events/KeyEvent.h
        src/Like/Events/MouseEvent.h
        src/Like/ImGui/ImGuiLayer.h
        src/Like/Renderer/Buffer.h
        src/Like/Renderer/GraphicsContext.h
        src/Like/Renderer/OrthographicCamera.h
        src/Like/Renderer/OrthographicCameraController.h
        src/Like/Renderer/RenderCommand.h
        src/Like/Renderer/Renderer.h
        src/Like/Renderer/Renderer2D.h
        src/Like/Renderer/RendererAPI.h
        src/Like/Renderer/Shader.h
        src/Like/Renderer/Texture.h
        src/Like/Renderer/VertexArray.h
        src/Platform/OpenGL/OpenGLBuffer.h
        src/Platform/OpenGL/OpenGLContext.h
        src/Platform/OpenGL/OpenGLRendererAPI.h
        src/Platform/OpenGL/OpenGLShader.h
        src/Platform/OpenGL/OpenGLTexture.h
        src/Platform/OpenGL/OpenGLVertexArray.h
        src/Platform/Windows/WindowsInput.h
        src/Platform/Windows/WindowsWindow.h
        src/Like.h
)

target_include_directories(Like
        PUBLIC
            src
            vendor/glad/include
            vendor/glfw/include
            vendor/glm
            vendor/imgui
            vendor/spdlog/include
            vendor/stb_image
)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)

target_link_libraries(Like
        PRIVATE
            glad
            glfw
            glm
)

target_precompile_headers(Like
        PRIVATE
            src/lkpch.h
)

target_compile_definitions(Like
        PRIVATE
        $<$<PLATFORM_ID:Windows>:LK_PLATFORM_WINDOWS>
        $<$<PLATFORM_ID:Darwin>:LK_PLATFORM_MACOS>
        $<$<PLATFORM_ID:Windows>:LK_BUILD_DLL>
        GLFW_INCLUDE_NONE
)

set_target_properties(Like PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        OBJECT_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin-int
)
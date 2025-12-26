project(Sandbox
        LANGUAGES CXX
)

add_executable(Sandbox)

target_sources(Sandbox
        PRIVATE
        src/SandboxApp.cpp
        src/Sandbox2D.cpp
)

target_include_directories(Sandbox
        PRIVATE
        src
        ${CMAKE_SOURCE_DIR}/Like/vendor/spdlog/include
        ${CMAKE_SOURCE_DIR}/Like/src
        ${CMAKE_SOURCE_DIR}/Like/vendor
        ${CMAKE_SOURCE_DIR}/Like/vendor/glm
)

target_link_libraries(Sandbox
        PRIVATE
            Like
)

target_compile_definitions(Sandbox
        PRIVATE
        $<$<PLATFORM_ID:Darwin>:LK_PLATFORM_MACOS>
)
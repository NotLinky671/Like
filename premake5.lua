workspace "Like"
    architecture "x64"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

    startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Like/vendor/GLFW/include"
IncludeDir["glad"] = "Like/vendor/glad/include"
IncludeDir["ImGui"] = "Like/vendor/imgui"
IncludeDir["glm"] = "Like/vendor/glm"

include "Like/vendor/GLFW"
include "Like/vendor/glad"
include "Like/vendor/imgui"

project "Like"
    location "Like"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    pchheader "lkpch.h"
    pchsource "Like/src/lkpch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    defines "_CRT_SECURE_NO_WARNINGS"

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links {
        "GLFW",
        "glad",
        "ImGui",
        "opengl32"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "LK_PLATFORM_WINDOWS",
            "LK_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configuretions.Debug"
        defines "LK_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configuretions.Release"
        defines "LK_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configuretions.Dist"
        defines "LK_DIST"
        runtime "Release"
        symbols "on"

    filter "action:vs*"
        buildoptions 
        { 
            "/utf-8"
        }

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "Like/vendor/spdlog/include",
        "Like/src",
        "Like/vendor",
        "%{IncludeDir.glm}"
    }

    links {
        "Like"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "LK_PLATFORM_WINDOWS"
        }

    filter "configuretions.Debug"
        defines "LK_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configuretions.Release"
        defines "LK_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configuretions.Dist"
        defines "LK_DIST"
        runtime "Release"
        symbols "on"

    filter "action:vs*"
        buildoptions { "/utf-8" }
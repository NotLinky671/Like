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

include "Like/vendor/GLFW"
include "Like/vendor/glad"
include "Like/vendor/imgui"

project "Like"
    location "Like"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    pchheader "lkpch.h"
    pchsource "Like/src/lkpch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.ImGui}"
    }

    links {
        "GLFW",
        "glad",
        "ImGui",
        "opengl32"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines {
            "LK_PLATFORM_WINDOWS",
            "LK_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configuretions.Debug"
        defines "LK_DEBUG"
        symbols "On"

    filter "configuretions.Release"
        defines "LK_RELEASE"
        optimize "On"

    filter "configuretions.Dist"
        defines "LK_DIST"
        symbols "On"

    filter "action:vs*"
        buildoptions { "/utf-8" }
        buildoptions { "/MD" }

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "Like/vendor/spdlog/include",
        "Like/src"
    }

    links {
        "Like"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines {
            "LK_PLATFORM_WINDOWS"
        }

    filter "configuretions.Debug"
        defines "LK_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configuretions.Release"
        defines "LK_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configuretions.Dist"
        defines "LK_DIST"
        buildoptions "/MD"
        symbols "On"

    filter "action:vs*"
        buildoptions { "/utf-8" }
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

include "Like/vendor/GLFW"

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
        "%{IncludeDir.GLFW}"
    }

    links {
        "GLFW",
        "opengl32"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines {
            "LK_PLATFORM_WINDOWS",
            "LK_BUILD_DLL"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
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
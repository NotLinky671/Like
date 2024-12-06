workspace "Like"
    architecture "x64"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

    startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Like"
    location "Like"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include"
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
        symbols "On"

    filter "configuretions.Release"
        defines "LK_RELEASE"
        optimize "On"

    filter "configuretions.Dist"
        defines "LK_DIST"
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
        symbols "On"

    filter "configuretions.Release"
        defines "LK_RELEASE"
        optimize "On"

    filter "configuretions.Dist"
        defines "LK_DIST"
        symbols "On"

    filter "action:vs*"
        buildoptions { "/utf-8" }
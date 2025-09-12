project "SliceEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    architecture "x64"

    targetdir ("")
    -- objdir ("bin-int/%{cfg.buildcfg}")

    files { "src/**.cpp", "src/**.h" }

    includedirs {
        "thirdparty/glew/GL",
        "thirdparty/glfw/include",
        "thirdparty/glm",
        "thirdparty/rttr/include/rttr",
        "thirdparty/xprop",
        "thirdparty/entt",
        "thirdparty/Jolt",
        "thirdparty/fmod/include",
        "src/pch"
    }

    libdirs {
        "thirdparty/glew/lib",
        "thirdparty/glfw/lib-vc2022",
        "thirdparty/rttr/lib"
    }

    links {
        "glew32",
        "opengl32",
        "glfw3",
        "rttr_core_s_d"
    }

    filter "configurations:EditorDebug" 
        links {
            "fmodL_vc"
        }
    
    filter "configurations:EditorRelease" 
        links {
            "fmod_vc"
        }

    pchheader "pch.h"
    pchsource "pch.cpp"
    
    -- filter "configurations:Release"
    -- postbuildcommands {
    --     '{COPY} SliceEngine.lib ../ReleaseLibs/SliceEngine.lib'
    -- }


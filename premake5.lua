workspace "Minecraft"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	startproject "Minecraft"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["glfw"] = "Minecraft/vendor/glfw/include"
IncludeDir["glad"] = "Minecraft/vendor/glad/include"
IncludeDir["glm"] = "Minecraft/vendor/glm"
IncludeDir["stb_image"] = "Minecraft/vendor/stb_image"
IncludeDir["yamlCpp"] = "Minecraft/vendor/yamlCpp/include"

include "Minecraft/vendor/glfw"
include "Minecraft/vendor/glad"
include "Minecraft/vendor/yamlCpp"

project "Minecraft"
	location "Minecraft"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Minecraft/src/pch.cpp"

	debugdir "%{wks.location}"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",

		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.stb_image}/src",
		"%{IncludeDir.yamlCpp}",
	}

	links
	{
		"GLFW",
		"GLAD",
		"opengl32.lib",
		"yamlCpp"
	}

	filter "system:windows"
		systemversion "latest"
		defines 
		{
			"MC_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE",
			"YAML_CPP_STATIC_DEFINE"
		}

	filter "configurations:Debug"
		defines
		{
			"MC_DEBUG",
			"MC_ENABLE_ASSERTS",
			"MC_LOG_LEVEL_TRACE"
		}
		symbols "on"

	filter "configurations:Release"
		defines
		{
			"MC_RELEASE",
			"MC_LOG_LEVEL_WARN"
		}
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines
		{
			"MC_DIST",
			"MC_LOG_LEVEL_INFO"
		}
		runtime "Release"
		optimize "on"
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

project "Minecraft"
	location "Minecraft"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	debugdir "%{wks.location}"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
	}

	filter "system:windows"
		systemversion "latest"
		defines 
		{
			"MC_PLATFORM_WINDOWS",
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
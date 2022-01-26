workspace "LostTomes"
	architecture "x86"

	configurations { "Debug", "Release" }

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "LostTomes"
	location "LostTomes"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "PCH.h"
	pchsource "LostTomes/src/PCH.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"vendor"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"LTOMES_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "LTOMES_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "LTOMES_RELEASE"
		optimize "On"
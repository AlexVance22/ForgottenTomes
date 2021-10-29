workspace "ForgottenTomes"
	architecture "x86"

	configurations { "Debug", "Release" }

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "ForgottenTomes"
	location "ForgottenTomes"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "PCH.h"
	pchsource "ForgottenTomes/src/PCH.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"../ForgottenTomes/vendor"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"FTOMES_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "FTOMES_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "FTOMES_RELEASE"
		optimize "On"
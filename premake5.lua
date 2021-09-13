workspace "br4in"
	configurations { "debug", "release" }

project "br4in"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	warnings "Extra"
	flags { "FatalWarnings" }

	targetdir "bin/%{cfg.buildcfg}"
	objdir "obj"

	files { "source/**.hpp", "source/**.cpp" }

	filter { "configurations:debug" }
		symbols "On"
		defines { "DEBUG" }

	filter { "configurations:release" }
		optimize "On"
		defines { "NDEBUG" }
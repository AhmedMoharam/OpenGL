workspace "OpenGL"
   configurations { "Debug", "Release" }
   platforms { "Win32", "Win64" }
   
	filter { "platforms:Win32" }
		system "Windows"
		architecture "x86"

	filter { "platforms:Win64" }
		system "Windows"
		architecture "x86_64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "OpenGL"
   kind "ConsoleApp"
   language "C++"
   location "OpenGL"
   targetdir ("bin/" .. outputdir)
   objdir ("bin-obj/" .. outputdir)

	files { "%{prj.name}/src/**.h", 
			"%{prj.name}/src/**.cpp" }

	includedirs {"%{prj.name}/Dependencies/glfw/%{cfg.system}-%{cfg.architecture}/include",
				 "%{prj.name}/Dependencies/glew/include"}

	libdirs {"%{prj.name}/Dependencies/glfw/%{cfg.system}-%{cfg.architecture}/lib-vc2017",
			 "%{prj.name}/Dependencies/glew/lib/%{cfg.system}-%{cfg.architecture}"}

	links {"glfw3.lib",
		   "glew32s.lib",
		   "opengl32.lib"}

	defines {"GLEW_STATIC"}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		postbuildcommands { "{COPY} Resources %{cfg.buildtarget.directory}/Resources" }


	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

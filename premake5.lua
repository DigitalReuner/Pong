workspace "Pong"
   configurations { "Debug", "Release" }
   startproject "App"

project "App"
   location "build"
   kind "WindowedApp"
   language "C++"
   cppdialect "C++latest"
   staticruntime "on"
   warnings "Extra"

   targetdir ("bin/%{cfg.buildcfg}")
   objdir ("bin-int/%{cfg.buildcfg}")

   files { "src/**.cpp", "include/**.h" }

   includedirs { "include" }

   filter "system:linux"
      systemversion "latest"
      links { "pthread" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

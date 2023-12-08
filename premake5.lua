-- premake5.lua
workspace "ogl-minecraft"
   configurations { "debug", "release" }
   location "build"

   warnings "Extra"

project "olg-minecraft"
   kind "WindowedApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"
   includedirs{"libs"}

   links {"glfw", "GL", "X11", "pthread", "Xrandr", "Xi", "dl"}

   files { "**.h", "**.cpp", "**.c" }

   filter "configurations:debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:release"
      defines { "NDEBUG" }
      optimize "On"

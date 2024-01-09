workspace "PixelEngine"  
    configurations { "Debug", "Release" } 
    location "PixelEngine"
    cppdialect "C++20"
    architecture "x86_64"
	startproject "Application"
    objdir ("bin")
    includedirs {"$(solutionDir)/PixelEngine/Dependencies"}

project "Application"  
    kind "WindowedApp"   
    language "C++"   
    location ("PixelEngine/Application")
    targetdir "Product/%{cfg.buildcfg}" 
    files { "PixelEngine/Application/**.h", "PixelEngine/Application/**.cpp" } 

    filter "configurations:Debug"
        defines { "PEDEBUG" }  
        symbols "On"
        kind "ConsoleApp"
        
    filter "configurations:Release"  
        defines { "PERELEASE" }    
        optimize "On" 
        kind "WindowedApp"

project "Core"  
    kind "StaticLib"   
    language "C++"   
    location ("PixelEngine/Core")
    targetdir "Product/%{cfg.buildcfg}" 
    files { "PixelEngine/Core/**.h", "PixelEngine/Core/**.cpp" } 

project "Dependencies"  
    kind "StaticLib"   
    language "C++"   
    location ("PixelEngine/Dependencies")
    targetdir "Product/%{cfg.buildcfg}" 
    files { "PixelEngine/Dependencies/**.h", "PixelEngine/Dependencies/**.cpp" } 
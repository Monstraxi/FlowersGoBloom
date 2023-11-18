project "FlowersGoBloom"
    kind "ConsoleApp"
    language "C++"
    
    files {"**.h", "**.cpp"}

    targetdir ("../bin/" .. output_path .. "/%{prj.name}")
    objdir ("../bin-int/" .. output_path .. "/%{prj.name}")

    includedirs {"%{include_path.SFML}"}

    filter "configurations:Debug"
        defines "DEBUG"
        symbols "on"
        libdirs {"%{lib_path.SFMLD}"}
        links {link["SFMLD"]}
    filter "configurations:Release"
        defines "RELEASE"
        optimize "on"
        libdirs {"%{lib_path.SFMLD}"}
        links {link["SFMLND"]}

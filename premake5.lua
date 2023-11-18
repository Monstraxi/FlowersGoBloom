workspace "FlowersGoBloom"
    architecture "x64"
    configurations {"Debug", "Release"}

    output_path = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    include_path = {}
    include_path["SFML"] = "../Dependencies/SFML/include"

    lib_path = {}
    lib_path["SFMLD"] = "../Dependencies/SFML/lib/debug"
    lib_path["SFMLND"] = "../Dependencies/SFML/lib/ndebug"

    link = {}
    link["SFMLD"] = {
        "opengl32.lib",
        "gdi32.lib",
        "freetype.lib",
        "winmm.lib",
        "sfml-graphics-s-d.lib",
        "sfml-system-s-d.lib",
        "sfml-window-s-d.lib",
    }

    link["SFMLND"] = {
        "opengl32.lib",
        "freetype.lib",
        "gdi32.lib",
        "winmm.lib",
        "sfml-graphics-s.lib",
        "sfml-system-s.lib",
        "sfml-window-s.lib",
    }

    include "FlowersGoBloom"
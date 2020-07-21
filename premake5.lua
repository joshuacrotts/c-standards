workspace "C-Standards"
        configurations { "Debug", "Release" }

        libdirs { os.findlib("SDL2") }
	includedirs { "/usr/include/SDL2" }

        kind "WindowedApp"
        language "C"

        links { "SDL2", "SDL2_ttf", "SDL2_mixer", "SDL2_image", "m" }


project "Game"
        targetdir "bin/%{cfg.buildcfg}"

        files {
		"**.h", "**.c"
	}
	
	print(files)

        filter "configurations:Debug"
                defines { "DEBUG" }
                symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		symbols "On"

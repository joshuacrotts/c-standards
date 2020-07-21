workspace "C-Standards"
        configurations { "Debug", "Release" }
        libdirs { os.findlib("SDL2") }
	includedirs { "/usr/include/SDL2" }

        kind "WindowedApp"
        language "C"
        makesettings [[
                CC = gcc
        ]]
        links { "mingw32", "SDL2main", "SDL2", "SDL2_ttf", "SDL2_mixer", "SDL2_image", "m" }


project "Game"  
        -- Builds to the current directory to avoid file issues. --
        targetdir ""

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

project "GLM"
    kind "StaticLib"
    language "C++"
    
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
        "glm/*.hpp",
		"glm/gtx/*.hpp",
		"glm/gtc/*.hpp",
		"glm/ext/*.hpp",
		"glm/detail/*.hpp",
		"glm/simd/*.hpp",
    }
    
	filter "system:windows"
        systemversion "latest"
        cppdialect "C++17"
        staticruntime "On"
        
    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"

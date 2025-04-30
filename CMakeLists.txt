cmake_minimum_required(VERSION "3.19.2")
set(CMAKE_CXX_STANDARD 20)

# Subdirectories/Library Paths #####################

set(IMGUI_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Shared/imgui")
set(STB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Shared/stb" )
add_subdirectory("Shared/SDL3")
add_subdirectory("Shared/ImNodeFlow")

####################################################

# ModIO Library ####################################

project(ModIO)

file(GLOB_RECURSE ENGINE_SOURCE CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/ModIO/Engine/src/*.cpp")

add_library(ModIO SHARED)

target_include_directories(ModIO PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/ModIO/Engine/include/")
target_sources(ModIO PRIVATE ${ENGINE_SOURCE})

target_compile_definitions(ModIO PRIVATE MOD_BUILD_DLL)

if(WIN32)
  target_compile_definitions(ModIO PRIVATE MOD_PLATFORM_WINDOWS)  
endif()

target_link_libraries(ModIO PRIVATE SDL3-shared)

# Sandbox Dev Environment For ModIO#################

project(Sandbox)

file(GLOB_RECURSE SANDBOX_SOURCE CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/ModIO/Sandbox/src/*.cpp")

add_executable(Sandbox ${SANDBOX_SOURCE})

if(WIN32)
  target_compile_definitions(Sandbox PRIVATE MOD_PLATFORM_WINDOWS)  
endif()

target_link_libraries(Sandbox PUBLIC ModIO)

####################################################

# ImGUI ############################################

set(IMGUI_BACKENDS_INCLUDE
        "${IMGUI_PATH}/backends/imgui_impl_sdl3.h"   
        "${IMGUI_PATH}/backends/imgui_impl_sdlrenderer3.h"   
)
set(IMGUI_BACKENDS_SOURCE
        "${IMGUI_PATH}/backends/imgui_impl_sdl3.cpp"   
        "${IMGUI_PATH}/backends/imgui_impl_sdlrenderer3.cpp" 
)

####################################################

# Application ######################################

project(Application)

file(GLOB_RECURSE APPLICATION_SOURCE CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Application/src/*.cpp")

add_executable(Application ${APPLICATION_SOURCE} )

target_include_directories(Application
    PRIVATE
    ${IMGUI_PATH} 
    "${IMGUI_PATH}/backends"
    ${STB_PATH}
    "${CMAKE_CURRENT_SOURCE_DIR}/Application/src"
)

target_sources(Application 
    PRIVATE
    ${IMGUI_SOURCE}
    ${IMGUI_BACKENDS_SOURCE}
    "${STB_PATH}/stb_image.cpp"
)

add_compile_definitions(Application PRIVATE IMGUI_DEFINE_MATH_OPERATORS)
target_compile_definitions(Application PRIVATE IMGUI_NODES_DATA="${IMGUI_NODES_PATH}/examples/data")  

if(WIN32)
  target_compile_definitions(Application PRIVATE MOD_PLATFORM_WINDOWS)  
endif()

target_link_libraries(Application PRIVATE ModIO)
target_link_libraries(Application PRIVATE SDL3-shared)
target_link_libraries(Application PRIVATE ImNodeFlow)

####################################################
cmake_minimum_required(VERSION "3.19.2")
set(CMAKE_CXX_STANDARD 20)

# Subdirectories/Library Paths #####################

set(IMGUI_NODES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Shared/imgui-node-editor")
add_subdirectory("Shared/SDL3")
add_subdirectory("${IMGUI_NODES_PATH}/external/imgui")
add_subdirectory("${IMGUI_NODES_PATH}/external/ScopeGuard")
add_subdirectory("${IMGUI_NODES_PATH}/external/stb_image")

####################################################

# ImGUI Node Editor Library ########################

project(ImGUI_Nodes)

set(IMGUI_NODES_SRC
        "${IMGUI_NODES_PATH}/crude_json.cpp"
        "${IMGUI_NODES_PATH}/crude_json.h"
        "${IMGUI_NODES_PATH}/imgui_bezier_math.h"
        "${IMGUI_NODES_PATH}/imgui_bezier_math.inl"
        "${IMGUI_NODES_PATH}/imgui_canvas.cpp"
        "${IMGUI_NODES_PATH}/imgui_canvas.h"
        "${IMGUI_NODES_PATH}/imgui_extra_math.h"
        "${IMGUI_NODES_PATH}/imgui_extra_math.inl"
        "${IMGUI_NODES_PATH}/imgui_node_editor.cpp"
        "${IMGUI_NODES_PATH}/imgui_node_editor.h"
        "${IMGUI_NODES_PATH}/imgui_node_editor_api.cpp"
        "${IMGUI_NODES_PATH}/imgui_node_editor_internal.h"
        "${IMGUI_NODES_PATH}/imgui_node_editor_internal.inl"
)

add_library(ImGUI_Nodes ${IMGUI_NODES_SRC})

target_include_directories(ImGUI_Nodes PRIVATE "${IMGUI_NODES_PATH}")

target_link_libraries(ImGUI_Nodes PRIVATE imgui)
target_link_libraries(ImGUI_Nodes PRIVATE ScopeGuard)
target_link_libraries(ImGUI_Nodes PRIVATE stb_image)

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

# Application ######################################

project(Application)

file(GLOB_RECURSE APPLICATION_SOURCE CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Application/src/*.cpp")

add_executable(Application ${APPLICATION_SOURCE})

if(WIN32)
  target_compile_definitions(Application PRIVATE MOD_PLATFORM_WINDOWS)  
endif()

target_link_libraries(Application PRIVATE ModIO)
target_link_libraries(Application PUBLIC SDL3-shared)
target_link_libraries(Application PRIVATE ImGUI_Nodes)


####################################################
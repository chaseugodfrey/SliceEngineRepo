# CMakeList.txt : CMake project for Slice Engine, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.26)

# Add source to this project's executable.
project(SliceEngine)
set(CMAKE_CXX_STANDARD 17)

# ---- SUBDIRS-----
add_subdirectory("Engine")
# EDITOR OPTION
option(USE_EDITOR "Build Editor" OFF)
if (USE_EDITOR)
    add_subdirectory("Editor")
    add_compile_definitions(EDITOR PRIVATE USE_EDITOR=1)
endif()

# ---- COMPILE DEFINITIONS -----
add_compile_definitions(LIB_DIR="${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/")
add_compile_definitions(ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Assets/")
add_compile_definitions(RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Resources/")

# ---- LIBRARIES -----
add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glfw/lib-vc2022/glfw3.lib)
target_include_directories(glfw INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glfw/include)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (USE_EDITOR)
add_library(imgui STATIC IMPORTED)
target_include_directories(Editor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(imgui INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui/include)
endif()

# ---- COMPILATION -----
# Retrieves all filenames with .cpp and adds it to variable SLICE_SOURCES
file (GLOB_RECURSE SLICE_SOURCES CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable (SliceEngine "main.cpp" ${SLICE_SOURCES})

# ----- PCH -----
target_precompile_headers(SliceEngine PUBLIC pch.h)
set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)

# ---- LINKING -----
target_include_directories(SliceEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(SliceEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}ThirdParty)
target_link_libraries(SliceEngine PRIVATE glfw) 
target_link_libraries(SliceEngine PRIVATE Engine)
if (USE_EDITOR)
    target_compile_definitions(SliceEngine PRIVATE USE_EDITOR=1)
    target_compile_definitions(SliceEngine PRIVATE EDITOR)
    target_link_libraries(SliceEngine PRIVATE Editor)
else()
    target_compile_definitions(SliceEngine PRIVATE USE_EDITOR=0)
endif()


# target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")




# ----- POST BUILD -----
# Copies all content from source assets folder into bin assets folder
add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/Assets
                ${CMAKE_CURRENT_BINARY_DIR}/Assets)

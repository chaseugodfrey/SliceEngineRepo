# CMakeList.txt : CMake project for Slice Engine, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.26)

# Add source to this project's executable.
project(SliceEngine)
set(CMAKE_CXX_STANDARD 17)

# ----- LIBRARIES -----
# GLFW
add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/lib-vc2022/glfw3.lib)
target_include_directories(glfw INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/includes)

# ---- COMPILATION -----
# Retrieves all filenames with .cpp and adds it to variable SLICE_SOURCES
file (GLOB_RECURSE SLICE_SOURCES CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable (SliceEngine "main.cpp" ${SLICE_SOURCES})
# add_executable(main main.cpp  "Slice_pch.h" "src/App.h"  "src/App.cpp" )
target_link_libraries(SliceEngine PRIVATE glfw) 
 
# target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
# target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

# ----- PCH -----
target_precompile_headers(SliceEngine PUBLIC Slice_pch.h)
set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)


# ----- POST BUILD -----
# Copies all content from source assets folder into bin assets folder
add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/assets
                ${CMAKE_CURRENT_BINARY_DIR}/assets)

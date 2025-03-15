# CMakeList.txt : CMake project for Slice Engine, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.2)

# Add source to this project's executable.
project(main)
set(CMAKE_CXX_STANDARD 17)

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/lib-vc2022/glfw3.lib)
target_include_directories(glfw INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/includes)

file (GLOB_RECURSE SLICE_SOURCES CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable (main "main.cpp" ${SLICE_SOURCES})
# add_executable(main main.cpp  "Slice_pch.h" "src/App.h"  "src/App.cpp" )
target_link_libraries(main PRIVATE glfw)

# target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
# target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

target_precompile_headers(main PUBLIC Slice_pch.h)
set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)


# TODO: Add tests and install targets if needed.

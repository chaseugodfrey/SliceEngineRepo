# CMakeList.txt : CMake project for Slice Engine, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.26)

# Add source to this project's executable.
project(SliceEngine)
set(CMAKE_CXX_STANDARD 17)

# ---- COMPILE DEFINITIONS -----
add_compile_definitions(LIB_DIR="${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/")
add_compile_definitions(ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Assets/")
add_compile_definitions(RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Resources/")
add_compile_definitions(GLEW_STATIC) # Ensure GLEW_STATIC is defined
# Generate a function to create a preprocessor definition for A


# ---- SUBDIRS-----
#add_subdirectory("Engine")
#target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# EDITOR OPTION
#option(USE_EDITOR "Build Editor" ON)
#if (USE_EDITOR)
#    add_subdirectory("Editor")
#    add_compile_definitions(EDITOR PUBLIC USE_EDITOR=1)
#endif()

# ---- LIBRARIES -----
# GLFW
add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glfw/lib-vc2022/glfw3.lib)
target_include_directories(glfw INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glfw/include)

find_package(OpenGL REQUIRED)
# GLEW
add_library(glew STATIC IMPORTED)
set_target_properties(glew PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glew/glew32s.lib)
target_include_directories(glew INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glew/GL)

#if (USE_EDITOR)
# IMGUI
#file(GLOB_RECURSE IMGUI_SOURCES 
#    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui/include/imgui*.cpp"
#)
#target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui)

#target_link_libraries(imgui PUBLIC glew glfw)
#endif()

#if (USE_EDITOR)
#target_include_directories(Editor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_include_directories(imgui INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui/include)
#endif()

# ---- COMPILATION -----
# Retrieves all filenames with .cpp and adds it to variable SLICE_SOURCES
file (GLOB_RECURSE SLICE_SOURCES CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/Engine/*.cpp")
add_executable (SliceEngine "main.cpp" ${SLICE_SOURCES})

# ----- PCH -----
target_precompile_headers(SliceEngine PUBLIC pch.h)
set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)

# ---- LINKING -----
target_include_directories(SliceEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(SliceEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty)
target_link_libraries(SliceEngine PRIVATE glew glfw ${OPENGL_LIBRARIES})

#if (USE_EDITOR)
#    target_compile_definitions(SliceEngine PRIVATE USE_EDITOR=1)
#    target_link_libraries(SliceEngine PRIVATE Editor)
#
#else()
#    target_compile_definitions(SliceEngine PRIVATE USE_EDITOR=0)
#endif()

# ----- POST BUILD -----
# Copies all content from source assets folder into bin assets folder
add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty
                ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/Assets
                ${CMAKE_CURRENT_BINARY_DIR}/Assets)

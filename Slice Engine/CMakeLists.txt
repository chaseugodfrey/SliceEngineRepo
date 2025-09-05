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

# EDITOR OPTION
option(USE_EDITOR "Build Editor" ON)
if (USE_EDITOR)
    add_compile_definitions(EDITOR PUBLIC USE_EDITOR=1)
endif()

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

# FMOD
add_library(fmod STATIC IMPORTED)
set_target_properties(fmod PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/fmod/lib/fmod.dll)
set_target_properties(fmod PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/fmod/lib/fmod_studio.dll)
target_include_directories(fmod INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/fmod/inc)

# JOLT
# --- Build Jolt from source (no prebuilt .lib) ---

# Tell Jolt where your ThirdParty root is (it expects PHYSICS_REPO_ROOT/Jolt)
set(PHYSICS_REPO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty")

# Choose features so your app and Jolt agree
set(ENABLE_OBJECT_STREAM OFF CACHE BOOL "" FORCE)               # -> JPH_OBJECT_STREAM OFF
set(FLOATING_POINT_EXCEPTIONS_ENABLED OFF CACHE BOOL "" FORCE)  # -> JPH_FLOATING_POINT_EXCEPTIONS_ENABLED OFF

# Keep debug renderer & profiler enebled in all configs
set(DEBUG_RENDERER_IN_DEBUG_AND_RELEASE ON CACHE BOOL "" FORCE) # -> JPH_DEBUG_RENDERER
set(PROFILER_IN_DEBUG_AND_RELEASE ON CACHE BOOL "" FORCE)       # -> JPH_PROFILE_ENABLED

# Pull in Jolt build and target ("Jolt")
include("${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/Jolt/Jolt.cmake")

# Link both your test and engine against the freshly built Jolt(will delete for testing purpose)
add_executable(JoltTest src/test.cpp)
target_link_libraries(JoltTest PRIVATE Jolt)

# DOTNET
# --- Adding dotnet framework ---

# Add external include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/dotnet/include)

# Set output directories for the Core project
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/build/lib)  # For .lib files (static libraries)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/build/bin)   # For .dll files (shared libraries)

# Add the Core library
#add_library(Core STATIC 
#    src/DotNetApp/Application.cpp
#    src/DotNetApp/Application.h
#)

# Define the source directory of the DLLs
#set(DLL_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/dotnet/bin")

# Define the output directory for the build
#set(DLL_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin")

# Add a custom command for the post-build event
#add_custom_command(TARGET your_target POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_directory
#    ${DLL_SOURCE_DIR} ${DLL_OUTPUT_DIR}
#    COMMENT "Copying DLLs to output directory"
#)

# IMGUI
file(GLOB_RECURSE IMGUI_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui/include/imgui*.cpp")
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glfw/include
)
target_link_libraries(imgui INTERFACE glfw)

# ---- COMPILATION -----
# Retrieves all filenames with .cpp and adds it to variable SOURCE_FILES
file (GLOB_RECURSE ENGINE_FILES CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/Engine/*.cpp")
file (GLOB_RECURSE EDITOR_FILES CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/Editor/*.cpp")
#file (GLOB_RECURSE EDITOR_FILES CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/DotNetApp/*.cpp")
add_executable (SliceEngine "main.cpp" ${ENGINE_FILES} ${EDITOR_FILES})

# Add DLL_API_EXPORT to the preprocessor definitions for the target
target_compile_definitions(SliceEngine PRIVATE DLL_API_EXPORT)

# ----- PCH -----
target_precompile_headers(SliceEngine PUBLIC pch.h)
set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)

# ---- LINKING -----
target_include_directories(SliceEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(SliceEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty)
target_link_libraries(SliceEngine PRIVATE glew glfw ${OPENGL_LIBRARIES})
target_link_libraries(SliceEngine PRIVATE imgui)
target_link_libraries(SliceEngine PRIVATE Jolt)

# ----- POST BUILD -----
# Copies all content from source assets folder into bin assets folder
add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty
                ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/Assets
                ${CMAKE_CURRENT_BINARY_DIR}/Assets)

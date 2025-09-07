cmake_minimum_required(VERSION 3.12)

# Enable C# language
project(SliceScripts LANGUAGES CSharp)

# Build a C# class library (.NET DLL)
add_library(SliceScripts SHARED
    ScriptManager.cs
)

# Set the output type to "Library" (not EXE)
set_target_properties(SliceScripts PROPERTIES
    VS_DOTNET_TARGET_FRAMEWORK_VERSION "net6.0"   # or v4.8 / net6.0 if SDK-style
    VS_DOTNET_REFERENCES "System"
)

get_filename_component(PARENT_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)

set(CHILD_DIR "${PARENT_DIR}/SliceScriptApi/out/build/x64-debug")

# Reference your C++/CLI DLL (ScriptAPI)
set_target_properties(SliceScripts PROPERTIES
    VS_DOTNET_REFERENCES "${CHILD_DIR}/SliceScriptAPI.dll"
)




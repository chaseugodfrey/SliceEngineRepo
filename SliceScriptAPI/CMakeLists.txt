cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)  # Use C++17 for C++/CLI

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("SliceScriptAPI")

# Enable C++/CLI with the /clr flag
add_compile_options("/clr")

# Add source to this project's executable (or library)
add_library(SliceScriptAPI SHARED "SliceScriptAPI.cpp" "SliceScriptAPI.h")

# Set the path where the Core library is located (adjust the path)
link_directories(../"Slice Engine" ${CMAKE_BINARY_DIR}/core_project_build)

# Link the Core library to ScriptAPI
target_link_libraries(SliceScriptAPI PRIVATE Core)

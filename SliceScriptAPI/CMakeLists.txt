cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)  # Use C++17 for C++/CLI

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

get_filename_component(PARENT_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)

set(CHILD_DIR "${PARENT_DIR}/Slice\ Engine/out/build/lib")

# Print the child directory path
message(STATUS "Child directory: ${CHILD_DIR}")
# Get only .lib files
file(GLOB LIB_FILES "${CHILD_DIR}/*.lib")

foreach(LIB_FILE ${LIB_FILES})
    message(STATUS "  ${LIB_FILE}")
endforeach()


project("SliceScriptAPI")

# Enable C++/CLI with the /clr flag
#add_compile_options("/clr")

# Conditionally set compile options based on configuration
if(MSVC)
    # Disable /RTC1 when using /clr, and we're in Debug configuration
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /GR- /D_ITERATOR_DEBUG_LEVEL=0 /MT")
    endif()
    # You can also apply other flags specific to Release mode here, if needed
endif()

# Add source to this project's executable (or library)
add_library(SliceScriptAPI SHARED "SliceScriptAPI.cpp" "SliceScriptAPI.h")


# Set the path where the Core library is located (adjust the path)
link_directories(${CHILD_DIR})

# Link the Core library to ScriptAPI
#target_link_libraries(SliceScriptAPI PRIVATE Core)
#target_link_libraries(SliceScriptAPI PRIVATE SliceEngine)
target_link_libraries(SliceScriptAPI "${CHILD_DIR}/SliceEngine.lib")

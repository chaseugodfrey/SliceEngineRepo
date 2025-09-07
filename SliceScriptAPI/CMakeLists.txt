cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)  # Use C++17 for C++/CLI

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "ProgramDatabase")
  #set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

get_filename_component(PARENT_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)

#set(CHILD_DIR "${PARENT_DIR}/Slice Engine/out/build/x64-debug")
    
project("SliceScriptAPI")

# Add source to this project's executable (or library)
add_library(SliceScriptAPI SHARED "SliceScriptAPI.cpp" "SliceScriptAPI.h")

# Enable C++/CLI
if (MSVC)
    # Enable C++/CLI
    set_property(TARGET SliceScriptAPI PROPERTY COMMON_LANGUAGE_RUNTIME "")
    set_property(TARGET SliceScriptAPI PROPERTY VS_GLOBAL_ExceptionHandling "Async")
    #target_compile_options(SliceScriptAPI PRIVATE /EHa)

    # Force /Zi instead of /ZI
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "ProgramDatabase")

    # Remove other bad defaults
    string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    string(REPLACE "/EHs"  "" CMAKE_CXX_FLAGS       "${CMAKE_CXX_FLAGS}")
    string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS       "${CMAKE_CXX_FLAGS}")
endif()

target_compile_definitions(SliceScriptAPI PRIVATE SLICESCRIPTAPI_EXPORTS)

# --- Imported library for SliceEngine ---
add_library(SliceEngine STATIC IMPORTED)

set_target_properties(SliceEngine PROPERTIES
    IMPORTED_LOCATION_DEBUG   "${PARENT_DIR}/Slice Engine/out/build/x64-debug/SliceEngine.lib"
)

# Link SliceEngine into SliceScriptAPI
#target_link_libraries(SliceScriptAPI PRIVATE SliceEngine)

# Full path to the .lib file
#set(CORE_LIB "${CHILD_DIR}/SliceEngine.lib")

# Link directly with the .lib file
#target_link_libraries(SliceScriptAPI PRIVATE "${CORE_LIB}")

# Link the Core library to ScriptAPI
#target_link_libraries(SliceScriptAPI "${CHILD_DIR}/SliceEngine.lib")


#target_link_libraries(SliceScriptAPI PRIVATE SliceEngine)

# Set the output directory for shared libraries (DLL)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/build/bin)

# Set the output directory for executables
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/build/bin)

# Set the output directory for static libraries (if needed)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/build/lib)

# Print the child directory path
message(STATUS "Child directory: ${CORE_LIB}")
# Get only .lib files
#file(GLOB LIB_FILES "${CHILD_DIR}/*.lib")

#foreach(LIB_FILE ${LIB_FILES})
#    message(STATUS "  ${LIB_FILE}")
#endforeach()

# Create the bin directory if it doesn't exist
#file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/out/build/bin)

# Set the path where the Core library is located (adjust the path)
#link_directories(${CHILD_DIR})
cmake_minimum_required (VERSION 3.26)
set(CMAKE_CXX_STANDARD 17)

project ("Editor")
add_compile_definitions(EDITOR)

# libraries
add_library(Editor STATIC
    SliceEditor.cpp
 )

target_include_directories(Editor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Editor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(Editor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty)

# Link libraries - this is key, Engine comes first
target_link_libraries(Editor PUBLIC imgui)
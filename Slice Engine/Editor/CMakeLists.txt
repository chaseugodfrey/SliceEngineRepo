cmake_minimum_required (VERSION 3.26)
set(CMAKE_CXX_STANDARD 17)

project ("Editor")

# libraries
add_library(Editor STATIC
    SliceEditor.cpp
)

# includes
target_include_directories(Editor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

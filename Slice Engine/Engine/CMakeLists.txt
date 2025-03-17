cmake_minimum_required (VERSION 3.26)
set(CMAKE_CXX_STANDARD 17)

project ("Engine")

# libraries
add_library(Engine STATIC
    SliceEngine.cpp
)

# includes
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

cmake_minimum_required(VERSION 3.10)
project(roessler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set compiler flags for coverage testing
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

# Include directories
include_directories(include)

# CAPD Group
add_subdirectory(CAPD)

add_library(roessler_lib src/roessler.cpp)
target_link_libraries(roessler_lib capd)

add_executable(roessler src/roessler_main.cpp)
target_link_libraries(roessler roessler_lib capd)

add_library(biffurcation_lib src/biffurcation.cpp)
target_link_libraries(biffurcation_lib capd)

add_executable(nonrig-biff src/nonrig_biff_main.cpp)
target_link_libraries(nonrig-biff biffurcation_lib capd)

# For the tests
enable_testing()
add_subdirectory(tests)

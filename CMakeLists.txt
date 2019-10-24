cmake_minimum_required (VERSION 2.6)
project (Median)
# The version number.
set (Median_VERSION_MAJOR 1)
set (Median_VERSION_MINOR 0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/MedianConfig.h.in"
  "${PROJECT_BINARY_DIR}/MedianConfig.h"
  )
 
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")
 
add_executable(Median Main.cpp Median.cpp PerformanceTest.cpp UnitTests.cpp RBTree.cpp MedianFactory.cpp)


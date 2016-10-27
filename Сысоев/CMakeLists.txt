cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME postfix)
project(${PROJECT_NAME})

# TODO(Kornyakov): not sure if these lines are needed
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})

set(MP2_LAB3_LIBRARY "${PROJECT_NAME}")
#set(MP2_LAB3_TESTS   "test_${PROJECT_NAME}")
set(MP2_LAB3_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/base")

#include_directories("${MP2_LAB3_INCLUDE}" gtest)

# BUILD
add_subdirectory(base)
#add_subdirectory(base_test)
add_subdirectory(gtest)

# REPORT
message( STATUS "")
message( STATUS "General configuration for ${PROJECT_NAME}")
message( STATUS "======================================")
message( STATUS "")
message( STATUS "   Configuration: ${CMAKE_BUILD_TYPE}")
message( STATUS "")

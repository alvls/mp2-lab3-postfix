cmake_minimum_required(VERSION 3.5)
project(mp2-lab3-postfix CXX)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

include_directories(base gtest)

# BUILD
add_subdirectory(base)
add_subdirectory(base_test)
add_subdirectory(gtest)

set(target postfix_test)

file(GLOB hdrs "*.h*" "../base/*.h")
file(GLOB srcs "*.cpp" "../base/postfix.cpp")

#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty")

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} gtest)

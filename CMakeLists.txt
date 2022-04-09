# 3.8 is required for CMAKE_CXX_STANDARD to be properly set to 17
cmake_minimum_required(VERSION 3.8)

add_subdirectory( googletest )

project(priority_queue)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(priority_queue_tests priority_queue_tests.cpp)

target_link_libraries(priority_queue_tests PUBLIC gtest gtest_main)

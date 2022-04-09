# 3.8 is required for CMAKE_CXX_STANDARD to be properly set to 17
cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory( googletest )

project(priority_queue)

add_executable(priority_queue_tests priority_queue_tests.cpp)
set_property(TARGET priority_queue_tests
			 PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_link_libraries(priority_queue_tests gtest_main)

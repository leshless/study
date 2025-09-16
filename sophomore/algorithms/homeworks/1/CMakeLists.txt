cmake_minimum_required(VERSION 3.14)
project(queue_test)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find GoogleTest package (system installation)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)  # GTest often requires threads

# Add your queue library
add_library(queue_lib queue.cpp queue.hpp)

# Create the test executable
add_executable(
  queue_test
  queue_test.cpp
)

# Link with system GoogleTest and your library
target_link_libraries(
  queue_test
  queue_lib
  GTest::gtest_main
  Threads::Threads
)

# Add include directories
target_include_directories(queue_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Enable testing
enable_testing()
add_test(NAME queue_test COMMAND queue_test)
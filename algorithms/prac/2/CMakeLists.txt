cmake_minimum_required(VERSION 3.14)
project(queue_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_library(queue_lib queue.cpp queue.hpp)

add_executable(
  queue_test
  queue_test.cpp
)

target_link_libraries(
  queue_test
  queue_lib
  GTest::gtest_main
  Threads::Threads
)

target_include_directories(queue_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()
add_test(NAME queue_test COMMAND queue_test)
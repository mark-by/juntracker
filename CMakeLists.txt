cmake_minimum_required(VERSION 3.15)
project(sql_wrapper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include_directories(include)
add_executable(sql_wrapper src/main.cpp src/sql_wrapper.cpp tests/include/test.h)
target_link_libraries(sql_wrapper pq)

add_subdirectory(tests)
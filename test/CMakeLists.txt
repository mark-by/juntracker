cmake_minimum_required(VERSION 3.13.4)
project(test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -ggdb3")



set(src/main.cpp
        src/tests.cpp)

# sets GTEST_INCLUDE_DIRS and GTEST_LIBRARIES
find_package( GTest REQUIRED )
# adds the gtest include directoryR
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test src/main.cpp src/tests.cpp)

# links gtest
target_link_libraries(test ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
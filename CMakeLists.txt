cmake_minimum_required(VERSION 3.15)

project(server)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -O0 -ggdb3")

add_subdirectory(src)

add_subdirectory(examples)

find_package(Boost COMPONENTS thread system REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(server ${Boost_LIBRARIES} ${serverlib})

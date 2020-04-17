cmake_minimum_required(VERSION 3.8)

project(server)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -O0 -ggdb3")

add_subdirectory(src)

add_subdirectory(examples)

include_directories("${PROJECT_SOURCE_DIR}/include/boost")
link_directories("${PROJECT_SOURCE_DIR}/include/boost/stage/lib")
include_directories("${PROJECT_SOURCE_DIR}/include/server")

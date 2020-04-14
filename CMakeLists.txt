cmake_minimum_required(VERSION 3.8)

project(html_template)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -O0 -ggdb3")

add_subdirectory(src)
add_subdirectory(examples)

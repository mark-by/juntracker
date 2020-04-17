cmake_minimum_required(VERSION 3.8)

project(juntracker)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -O0 -ggdb3")

configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

include_directories("${PROJECT_SOURCE_DIR}/include/boost")
link_directories("${PROJECT_SOURCE_DIR}/include/boost/stage/lib")
include_directories("${PROJECT_SOURCE_DIR}/include/templates")

add_subdirectory(src/templates)
add_subdirectory(examples)

enable_testing()
add_subdirectory(test)

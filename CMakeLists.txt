cmake_minimum_required(VERSION 3.8)

project(juntracker)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -O0 -ggdb3 -DASIO_STANDALONE -lboost_system")

configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)
set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
include_directories("${PROJECT_SOURCE_DIR}/include/boost")
link_directories("${PROJECT_SOURCE_DIR}/include/boost/stage/lib")

include_directories("${PROJECT_SOURCE_DIR}/include/core")
include_directories("${PROJECT_SOURCE_DIR}/include/templates")
include_directories("${PROJECT_SOURCE_DIR}/include/server")
include_directories("${PROJECT_SOURCE_DIR}/include/database")

add_subdirectory(src/templates)
add_subdirectory(src/wrapper)
add_subdirectory(src/core)
add_subdirectory(src/server)

add_subdirectory(examples)

enable_testing()
#add_subdirectory(test/db_test)
add_subdirectory(test/templates_test)
#add_subdirectory(test/server_test)
#add_subdirectory(test/core_test)

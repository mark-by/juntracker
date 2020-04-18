include_directories("${PROJECT_SOURCE_DIR}/include/boost")
link_directories("${PROJECT_SOURCE_DIR}/include/boost/stage/lib")
include_directories("${PROJECT_SOURCE_DIR}/include/server")

add_executable(server server_example.cpp)

target_link_libraries(server boost_thread pthread)

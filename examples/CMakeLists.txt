include_directories("${PROJECT_SOURCE_DIR}/include/boost")
include_directories("${PROJECT_SOURCE_DIR}/include/templates")
include_directories("${PROJECT_SOURCE_DIR}/include/server")

link_directories("${PROJECT_SOURCE_DIR}/include/boost/stage/lib")

add_executable(context context_example.cpp)
add_executable(node node_example.cpp)
add_executable(loader loader_example.cpp)
add_executable(server server_example.cpp)

target_link_libraries(node ${templates})
target_link_libraries(loader ${templates})
target_link_libraries(server boost_thread pthread)
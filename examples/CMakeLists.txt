include_directories("${PROJECT_SOURCE_DIR}/include/boost")
include_directories("${PROJECT_SOURCE_DIR}/include/templates")
include_directories("${PROJECT_SOURCE_DIR}/include/server")

link_directories("${PROJECT_SOURCE_DIR}/include/boost/stage/lib")

#add_executable(context context_example.cpp)
#add_executable(node node_example.cpp)
#add_executable(template template_example.cpp)
#add_executable(server server_example.cpp)
#add_executable(http_example http_example.cpp)
add_executable(render render.cpp)
#
#target_link_libraries(node templates)
#target_link_libraries(template templates boost_filesystem)
target_link_libraries(render templates boost_filesystem)
#target_link_libraries(server boost_thread pthread)
#target_link_libraries(http_example http boost_date_time)

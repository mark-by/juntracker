include_directories("${PROJECT_SOURCE_DIR}/include/boost")
include_directories("${PROJECT_SOURCE_DIR}/include/templates")
include_directories("${PROJECT_SOURCE_DIR}/include/server")

set(CURL_LIBRARY "-lcurl")

add_executable(context context_example.cpp)
add_executable(node node_example.cpp)
add_executable(template template_example.cpp)
add_executable(server server_example.cpp)
add_executable(http_example http_example.cpp)
add_executable(render render.cpp)
target_link_libraries(node templates)
target_link_libraries(server
        boost_thread
        http
        boost_date_time
        pthread
        server_lib
        api
        templates
        sql_wrapper_lib pq
        boost_filesystem
        ${CURL_LIBRARIES}
        )
target_link_libraries(render templates boost_filesystem)
target_link_libraries(http_example http boost_date_time)

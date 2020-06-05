include_directories("${PROJECT_SOURCE_DIR}/include/database")

file(GLOB db_source "${PROJECT_SOURCE_DIR}/src/wrapper/*.cpp")
add_executable(sql_wrapper ${db_source})

add_library(
        sql_wrapper_lib STATIC
        ${db_source}
        )

target_link_libraries(sql_wrapper pq boost_date_time boost_filesystem http)

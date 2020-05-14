include_directories("${PROJECT_SOURCE_DIR}/include/database")

set(db_source
        main.cpp
        sql_wrapper.cpp
        course.cpp
        teacher.cpp
        student.cpp user.cpp
        visit.cpp
        payment.cpp
        payment_history.cpp
        visit_history.cpp)

add_executable(sql_wrapper ${db_source})
add_library(
        sql_wrapper_lib STATIC
        ${db_source}
        )

target_link_libraries(sql_wrapper pq)
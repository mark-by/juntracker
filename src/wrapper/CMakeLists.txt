include_directories("${PROJECT_SOURCE_DIR}/include/database")

set(db_source
        course.cpp
        lesson.cpp
        main.cpp
        payment.cpp
        payment_history.cpp
        schedule.cpp
        session.cpp
        sql_wrapper.cpp
        student.cpp
        teacher.cpp
        user.cpp
        visit.cpp
        visit_history.cpp)

add_executable(sql_wrapper ${db_source})
add_library(
        sql_wrapper_lib STATIC
        ${db_source}
        )

target_link_libraries(sql_wrapper pq boost_date_time boost_filesystem)

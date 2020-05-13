include_directories("${PROJECT_SOURCE_DIR}/include/database")

add_library(
        sql_wrapper STATIC
        main.cpp sql_wrapper.cpp course.cpp
        teacher.cpp student.cpp user.cpp visit.cpp
        payment.cpp payment_history.cpp visit_history.cpp
        )

target_link_libraries(sql_wrapper pq)
include_directories("${PROJECT_SOURCE_DIR}/include/database")

add_executable(sql_wrapper main.cpp sql_wrapper.cpp course.cpp teacher.cpp student.cpp user.cpp visit.cpp)
target_link_libraries(sql_wrapper pq)
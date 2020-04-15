include_directories(include)

add_executable(sql_wrapper src/main.cpp src/sql_wrapper.cpp tests/include/test.h)
target_link_libraries(sql_wrapper pq)

add_subdirectory(tests)
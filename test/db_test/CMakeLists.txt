find_package(Threads REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/include/database")
include_directories("${PROJECT_SOURCE_DIR}/test/include")
include_directories("${PROJECT_SOURCE_DIR}/include/boost")

file(GLOB db_tests *.cpp)

add_executable(
        run_db_tests
        src/main.cpp src/test.cpp)

target_link_libraries(
        run_db_tests
        pq
        sql_wrapper
        gtest_main
        stdc++fs
        pthread
)

add_test(NAME run_db_tests
        COMMAND run_db_tests)

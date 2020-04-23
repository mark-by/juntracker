find_package(Threads REQUIRED)
include_directories("${PROJECT_SOURCE_DIR}/include/database")
include_directories("${PROJECT_SOURCE_DIR}/test/include")

add_executable(
        run_tests
        src/main.cpp src/test.cpp
)

target_link_libraries(
        run_tests
        pq
        gtest_main
        stdc++fs
        pthread
)

add_test(
        NAME run_tests
        COMMAND run_tests
)

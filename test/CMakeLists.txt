find_package(Threads REQUIRED)
include_directories("${PROJECT_SOURCE_DIR}/include/database")
include_directories("${PROJECT_SOURCE_DIR}/test/include")

add_executable(
        tests
        src/main.cpp src/test.cpp
)

target_link_libraries(tests pq stdc++fs)

add_test(
        NAME BaseTest
        COMMAND tests ${CMAKE_SOURCE_DIR}/project/tests/data --gtest_filter=-*Extra*
)

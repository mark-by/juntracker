find_package(GTest REQUIRED)
include_directories("${GTEST_INCLUDE_DIRS}")

find_package(Threads REQUIRED)

include_directories(include)

add_executable(
        tests
        src/main.cpp src/test.cpp
)

target_link_libraries(tests pq stdc++fs)

add_test(
        NAME BaseTest
        COMMAND tests ${CMAKE_SOURCE_DIR}/project/tests/data --gtest_filter=-*Extra*
)

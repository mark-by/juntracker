find_package(Threads REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/include/core")
include_directories("${PROJECT_SOURCE_DIR}/test/include")
include_directories("${PROJECT_SOURCE_DIR}/include/boost")

file(GLOB core_tests *.cpp)

add_executable(
        run_core_tests
        main.cpp test_serializers.cpp)

target_link_libraries(
        run_core_tests
        pq
        api
        gtest_main
        stdc++fs
        pthread
)

add_test(NAME run_core_tests
        COMMAND run_core_tests)

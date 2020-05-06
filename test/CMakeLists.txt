find_package(Threads REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/include/database")
include_directories("${PROJECT_SOURCE_DIR}/test/include")
include_directories("${PROJECT_SOURCE_DIR}/include/templates")
include_directories("${PROJECT_SOURCE_DIR}/include/boost")


file(GLOB tests *.cpp)

add_executable(
        run_tests
        src/main.cpp src/test.cpp
        ../include/database/abstract_db.h
        ${tests})

target_link_libraries(
        run_tests
        templates
        pq
        gtest_main
        stdc++fs
        pthread
)

add_test(NAME run_tests
        COMMAND run_tests)

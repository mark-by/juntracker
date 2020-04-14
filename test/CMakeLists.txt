find_package(Threads REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/include/boost")
include_directories("${PROJECT_SOURCE_DIR}/include/templates")

file(GLOB tests
        node.cpp
        context.cpp
        main.cpp
        )

add_executable(run_tests
        ${tests}
        )

target_link_libraries(run_tests
        templates
        gtest_main
        pthread
        )

add_test(NAME run_tests
        COMMAND run_tests)

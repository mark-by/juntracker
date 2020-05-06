find_package(Threads REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/include/templates")
include_directories("${PROJECT_SOURCE_DIR}/include/boost")


file(GLOB tests *.cpp)

add_executable(
        run_templates_tests
        ${tests})

target_link_libraries(
        run_tests
        templates
        gtest_main
        pthread
        boost_filesystem
        )

add_test(NAME run_templates_tests
        COMMAND run_templates_tests)

find_package(Threads REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/include/templates")
include_directories("${PROJECT_SOURCE_DIR}/include/boost")


file(GLOB templates_tests *.cpp)

add_executable(
        run_templates_tests
        ${templates_tests})

target_link_libraries(
        run_templates_tests
        templates
        gtest_main
        pthread
)

add_test(NAME run_templates_tests
        COMMAND run_templates_tests)

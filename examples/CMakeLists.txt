include_directories("${PROJECT_SOURCE_DIR}/include/boost")
include_directories("${PROJECT_SOURCE_DIR}/include/templates")
#include_directories("${PROJECT_SOURCE_DIR}/src/templates")

add_executable(context context_example.cpp)
add_executable(node node_example.cpp)
add_executable(loader loader_example.cpp)

target_link_libraries(node lib_templates)
target_link_libraries(loader lib_templates)

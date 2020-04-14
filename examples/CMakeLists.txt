include_directories("${PROJECT_SOURCE_DIR}/include/boost")
include_directories("${PROJECT_SOURCE_DIR}/include/templates")
include_directories("${PROJECT_SOURCE_DIR}/src/templates")

add_executable(context context_example.cpp)
add_executable(node node_example.cpp ${sorce})


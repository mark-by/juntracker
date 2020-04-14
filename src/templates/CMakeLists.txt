include_directories("${PROJECT_SOURCE_DIR}/include/boost")
include_directories("${PROJECT_SOURCE_DIR}/include/templates")

set(node_source
        node/node.cpp
        node/node_list.cpp )

set(loader_source
        loader/loader.cpp)


add_library(templates STATIC ${node_source} ${loader_source})
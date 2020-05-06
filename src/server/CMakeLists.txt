include_directories("${PROJECT_SOURCE_DIR}/include/boost")
include_directories("${PROJECT_SOURCE_DIR}/include/server")
link_directories("${PROJECT_SOURCE_DIR}/include/boost/stage/lib")

file(GLOB FILES "${PROJECT_SOURCE_DIR}/src/server/*.cpp")

set(server_source ${FILES})

add_library(serverlib STATIC ${server_source})

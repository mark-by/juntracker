include_directories("${PROJECT_SOURCE_DIR}/include/boost")
include_directories("${PROJECT_SOURCE_DIR}/include/server")
link_directories("${PROJECT_SOURCE_DIR}/include/boost/stage/lib")

file(GLOB FILES "${PROJECT_SOURCE_DIR}/src/server/*.cpp")
set(server_source ${FILES}
        http/request.cpp
        http/response.cpp
        http/datetime.cpp)

set(http_source
        http/request.cpp
        http/response.cpp
        http/datetime.cpp)
add_library(server_lib STATIC ${server_source})
add_library(http STATIC ${http_source})

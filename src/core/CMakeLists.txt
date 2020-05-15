include_directories("${PROJECT_SOURCE_DIR}/include/boost")
link_directories("${PROJECT_SOURCE_DIR}/include/boost/stage/lib")
include_directories("${PROJECT_SOURCE_DIR}/include/core")

file(GLOB FILES "${PROJECT_SOURCE_DIR}/src/core/*.cpp")

set(core_source ${FILES})

add_library(core_lib STATIC ${core_source})

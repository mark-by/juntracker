include_directories("${PROJECT_SOURCE_DIR}/include/boost")
link_directories("${PROJECT_SOURCE_DIR}/include/boost/stage/lib")
include_directories("${PROJECT_SOURCE_DIR}/include/core")
include_directories("${PROJECT_SOURCE_DIR}/include/database")
include_directories("${PROJECT_SOURCE_DIR}/include/templates")

set(api_source
        UserAPI.cpp
        AdminAPI.cpp
        TeacherAPI.cpp
        CustomerAPI.cpp)

add_library(api STATIC ${api_source})

include_directories("${PROJECT_SOURCE_DIR}/include/boost")
include_directories("${PROJECT_SOURCE_DIR}/include/core")
link_directories("${PROJECT_SOURCE_DIR}/include/boost/stage/lib")

include_directories("${PROJECT_SOURCE_DIR}/include/core")
include_directories("${PROJECT_SOURCE_DIR}/include/database")
include_directories("${PROJECT_SOURCE_DIR}/include/templates")

set(api_source
        API.cpp
        UserAPI.cpp
        AdminAPI.cpp
        TeacherAPI.cpp
        CustomerAPI.cpp
        StaffAPI.cpp)

add_library(api STATIC ${api_source})

include_directories("${PROJECT_SOURCE_DIR}/include/boost")
link_directories("${PROJECT_SOURCE_DIR}/include/boost/stage/lib")
include_directories("${PROJECT_SOURCE_DIR}/include/core")


add_executable(api main.cpp AdminAPI.cpp TeacherAPI.cpp CustomerAPI.cpp ManagerStudent.cpp ManagerCourse.cpp ManagerJournal.cpp
        ManagerPaymentHistory.cpp ManagerSchedule.cpp ManagerVisitHistory.cpp)
target_link_libraries(api)
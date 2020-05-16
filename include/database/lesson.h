#ifndef DATABASE_LESSON_H
#define DATABASE_LESSON_H

#include <string>
#include <vector>
#include <utility>

#include "teacher.h"
#include "student.h"
#include "sql_wrapper.h"

class Lesson {
public:
//    Lesson(SqlWrapper& postgres)
//        : postgres(postgres) {}

    explicit Lesson(int id, int cabinet, Teacher tutor, std::vector<Student>& students,
                    std::pair<int, int>& start_time, std::pair<int, int>& end_time)
            : id(id)
            , cabinet(cabinet)
            , tutor(tutor)
            , students(students)
            , start_time(start_time)
            , end_time(end_time) {}

 private:
    int id;
    int cabinet;
    Teacher tutor;
    std::vector<Student> students;
    std::pair<int, int> start_time;
    std::pair<int, int> end_time;

    SqlWrapper postgres;
};

#endif  // DATABASE_LESSON_H

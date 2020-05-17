#ifndef DATABASE_LESSON_H
#define DATABASE_LESSON_H

#include <string>
#include <vector>
#include <utility>

#include "course.h"

class Lesson {
public:
    Lesson(SqlWrapper& postgres)
        : postgres(postgres) {}

    explicit Lesson(int id, std::string& title, int cabinet, int teacher_id, std::vector<Student>& students,
            std::pair<int, int>& start_time, std::pair<int, int>& end_time)
            : id(id)
            , title(title)
            , cabinet(cabinet)
            , teacher_id(teacher_id)
            , students(students)
            , start_time(start_time)
            , end_time(end_time) {}


 private:
    int id;
    std::string title;
    int cabinet;
    int teacher_id;
    std::vector<Student> students;
    std::pair<int, int> start_time;
    std::pair<int, int> end_time;

    SqlWrapper postgres;
};

#endif  // DATABASE_LESSON_H

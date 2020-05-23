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

    explicit Lesson(int id, int course_id, int cabinet, int teacher_id, std::string weekday,
            std::string& start_time, std::string& end_time, int day_id)
            : id(id)
            , course_id(course_id)
            , cabinet(cabinet)
            , teacher_id(teacher_id)
            , weekday(weekday)
            , start_time(start_time)
            , end_time(end_time)
            , day_id(day_id) {}

    std::vector<Student> get_students(int l_id) const;
    Teacher get_teacher(int l_id) const;
    std::string get_weekday(std::string d_date) const;

    Lesson get_lesson(int d_id) const;
    int add_lesson(const Lesson& day) const;
    int delete_lesson(int d_id) const;


 private:
    int id;
    int course_id;
    int cabinet;
    int teacher_id;
    std::string weekday;
    std::string start_time;
    std::string end_time;
    int day_id;



    SqlWrapper postgres;
};

#endif  // DATABASE_LESSON_H

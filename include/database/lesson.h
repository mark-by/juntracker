#ifndef INCLUDE_DATABASE_LESSON_H
#define INCLUDE_DATABASE_LESSON_H

#include "teacher.h"
#include "student.h"
#include "cabinet.h"

class Lesson {
public:
    explicit Lesson(int _id, int _course_id, int _cabinet_id, int _teacher_id, int _weekday,
            const std::string& _start_time, const std::string& _end_time, int _school_id):
            _id(_id),
            _course_id(_course_id),
            _cabinet_id(_cabinet_id),
            _teacher_id(_teacher_id),
            _weekday(_weekday),
            _start_time(_start_time),
            _end_time(_end_time),
            _school_id(_school_id) {}

    std::vector<Student> get_students() const;
    Teacher get_teacher() const;
    Course get_course() const;
    Cabinet get_cabinet() const;

    static Lesson get_lesson(int lesson_id);
    static int save(int course_id, int cabinet_id, int teacher_id, int weekday,
            const std::string& start_time, const std::string& end_time, int school_id));
    static int remove(int lesson_id);

    int id() const { return _id; }
    int cabinet() const { return _cabinet_id; }
    int weekday() const { return _weekday; }
    std::string start_time() const { return _start_time; }
    std::string end_time() const { return _end_time; }

 private:
    int _id;
    int _course_id;
    int _cabinet_id;
    int _teacher_id;
    int _weekday;
    std::string _start_time;
    std::string _end_time;
    int _school_id;
};

#endif  // INCLUDE_DATABASE_LESSON_H

#ifndef INCLUDE_DATABASE_LESSON_H
#define INCLUDE_DATABASE_LESSON_H

#include "teacher.h"
#include "student.h"

class Lesson {
public:
    explicit Lesson(int _id, int _cabinet, int _weekday,
            const std::string& _start_time, const std::string& _end_time)
            : _id(_id)
            , _cabinet(_cabinet)
            , _weekday(_weekday)
            , _start_time(_start_time)
            , _end_time(_end_time) {}

    std::vector<Student> get_students() const;
    Teacher get_teacher() const;
    std::string get_title() const;

    static Lesson get_lesson(int lesson_id);
    static int save(int cabinet, const std::string& weekday, const std::string& start, const std::string& end);
    static int remove(int lesson_id);

    int id() const { return _id; }
    int cabinet() const { return _cabinet; }
    int weekday() const { return _weekday; }
    std::string start_time() const { return _start_time; }
    std::string end_time() const { return _end_time; }

 private:
    int _id;
    int _cabinet;
    int _weekday;
    std::string _start_time;
    std::string _end_time;
};

#endif  // INCLUDE_DATABASE_LESSON_H

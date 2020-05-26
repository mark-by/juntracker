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

    explicit Lesson(int _id, int _course_id, int _cabinet, int _teacher_id, std::string _weekday,
            std::string& _start_time, std::string& _end_time, int _day_id)
            : _id(_id)
            , _course_id(_course_id)
            , _cabinet(_cabinet)
            , _teacher_id(_teacher_id)
            , _weekday(_weekday)
            , _start_time(_start_time)
            , _end_time(_end_time)
            , _day_id(_day_id) {}

    std::vector<Student> get_students(int l_id) const;
    [[nodiscard]] Teacher get_teacher(int l_id) const;
    [[nodiscard]] std::string get_title(int l_id) const;
    [[nodiscard]] std::string get_weekday(int l_id) const;
    [[nodiscard]] std::string get_start(int l_id) const;
    [[nodiscard]] std::string get_end(int l_id) const;

    Lesson get_lesson(int l_id) const;
    int add_lesson(const Lesson& day) const;
    int delete_lesson(int d_id) const;

    [[nodiscard]] int id() const { return _id; }
    [[nodiscard]] int course_id() const { return _course_id; }
    [[nodiscard]] int cabinet() const { return _cabinet; }
    [[nodiscard]] int teacher_id() const { return _teacher_id; }
    [[nodiscard]] std::string weekday() const { return _weekday; }
    [[nodiscard]] std::string start_time() const { return _start_time; }
    [[nodiscard]] std::string end_time() const { return _end_time; }
    [[nodiscard]] int day_id() const { return _day_id; }

 private:
    int _id;
    int _course_id;
    int _cabinet;
    int _teacher_id;
    std::string _weekday;
    std::string _start_time;
    std::string _end_time;
    int _day_id;



    SqlWrapper postgres;
};

#endif  // DATABASE_LESSON_H

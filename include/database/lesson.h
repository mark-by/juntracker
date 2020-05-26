#ifndef INCLUDE_DATABASE_LESSON_H
#define INCLUDE_DATABASE_LESSON_H

#include "course.h"

class Lesson {
public:
    Lesson(SqlWrapper& postgres)
        : postgres(postgres) {}

    explicit Lesson(int _id, int _cabinet, std::string& _weekday,
            std::string& _start_time, std::string& _end_time, SqlWrapper postgres)
            : _id(_id)
            , _cabinet(_cabinet)
            , _weekday(_weekday)
            , _start_time(_start_time)
            , _end_time(_end_time)
            , postgres(postgres) {}

    std::vector<Student> get_students() const;
    Teacher get_teacher(int l_id) const;
    std::string get_title(int l_id) const;

    static Lesson get_lesson(int lesson_id);
    static int save(int cabinet, const std::string& weekaday, const std::string& start, const std::string& end);
    static int remove(int lesson_id);

    int id() const { return _id; }
    int cabinet() const { return _cabinet; }
    std::string weekday() const { return _weekday; }
    std::string start_time() const { return _start_time; }
    std::string end_time() const { return _end_time; }

 private:
    int _id;
    int _cabinet;
    std::string _weekday;
    std::string _start_time;
    std::string _end_time;

    SqlWrapper postgres;
};

#endif  // INCLUDE_DATABASE_LESSON_H

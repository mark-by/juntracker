#ifndef DATABASE_LESSON_H
#define DATABASE_LESSON_H

#include "course.h"

class Lesson {
public:
    Lesson(SqlWrapper& postgres)
        : postgres(postgres) {}

    explicit Lesson(int _id, int _cabinet, std::string _weekday,
            std::string& _start_time, std::string& _end_time)
            : _id(_id)
            , _cabinet(_cabinet)
            , _weekday(_weekday)
            , _start_time(_start_time)
            , _end_time(_end_time) {}

    std::vector<Student> get_students() const;
    [[nodiscard]] Teacher get_teacher() const;
    [[nodiscard]] std::string get_title() const;

    static Lesson get_lesson(int lesson_id);
    static int save(int cabinet, const std::string& weekaday, const std::string& start, const std::string& end);
    static int remove(int lesson_id);

    [[nodiscard]] int id() const { return _id; }
    [[nodiscard]] int cabinet() const { return _cabinet; }
    [[nodiscard]] std::string weekday() const { return _weekday; }
    [[nodiscard]] std::string start_time() const { return _start_time; }
    [[nodiscard]] std::string end_time() const { return _end_time; }

 private:
    int _id;
    int _cabinet;
    std::string _weekday;
    std::string _start_time;
    std::string _end_time;

    SqlWrapper postgres;
};

#endif  // DATABASE_LESSON_H

#ifndef DATABASE_SCHEDULE_H
#define DATABASE_SCHEDULE_H

#include "lesson.h"

class Schedule {
public:
    explicit Schedule(std::vector<Lesson> lessons)
        : lessons(lessons) {}

    std::vector<Lesson> get_schedule_by_student(int s_id) const;
    std::vector<Lesson> get_schedule_by_course(int c_id) const;
    std::vector<Lesson> get_schedule_by_teacher(int t_id) const;

private:
    std::vector<Lesson> lessons;
};

#endif  // DATABASE_SCHEDULE_H

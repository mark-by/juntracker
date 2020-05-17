#ifndef DATABASE_SCHEDULE_H
#define DATABASE_SCHEDULE_H

#include "day.h"

class Schedule {
public:
    Schedule(SqlWrapper& postgres)
        : postgres(postgres) {}
    explicit Schedule(std::vector<Day> days)
        : days(days) {}

    std::vector<Day> get_schedule_by_student(int s_id) const;
    std::vector<Day> get_schedule_by_course(int c_id) const;
    std::vector<Day> get_schedule_by_teacher(int t_id) const;

private:
    std::vector<Day> days;

    SqlWrapper postgres;
};

#endif  // DATABASE_SCHEDULE_H

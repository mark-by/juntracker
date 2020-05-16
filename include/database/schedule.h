#ifndef DATABASE_SCHEDULE_H
#define DATABASE_SCHEDULE_H

#include "day.h"

class Schedule {
public:
    Schedule(SqlWrapper& postgres)
            : postgres(postgres) {}
    explicit Schedule(std::vector<Day> days)
            : days(days) {}

private:
    std::vector<Day> days;

    SqlWrapper postgres;
};

#endif  // DATABASE_SCHEDULE_H

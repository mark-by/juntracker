#ifndef DATABASE_DAY_H
#define DATABASE_DAY_H

#include <string>
#include <vector>

#include "lesson.h"

class Day {
 public:
    Day(SqlWrapper& postgres)
        : postgres(postgres) {}
    explicit Day(int id, std::string& week_day, std::string& date, int lesson_id)
        : id(id)
        , week_day(week_day)
        , date(date)
        , lesson_id(lesson_id) {}

 private:
    int id;
    std::string week_day;
    std::string date;
    int lesson_id;

    SqlWrapper postgres;
};

#endif  // DATABASE_DAY_H

#ifndef DATABASE_DAY_H
#define DATABASE_DAY_H

#include <string>
#include <vector>

#include "lesson.h"

class Day {
 public:
    Day(SqlWrapper& postgres)
        : postgres(postgres) {}
    explicit Day(int id, std::string& week_day, std::string& date, std::vector<Lesson>& lessons)
        : id(id)
        , week_day(week_day)
        , date(date)
        , lessons(lessons) {}

 private:
    int id;
    std::string week_day;
    std::string date;
    std::vector<Lesson> lessons;

    SqlWrapper postgres;
};

#endif  // DATABASE_DAY_H

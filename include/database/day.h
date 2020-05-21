#ifndef DATABASE_DAY_H
#define DATABASE_DAY_H

#include <string>
#include <vector>

#include "lesson.h"

class Day {
 public:
    Day(SqlWrapper& postgres)
        : postgres(postgres) {}
    explicit Day(int id, std::string& weekday, std::string& date)
        : id(id)
        , weekday(weekday)
        , date(date) {}

    std::string get_weekday(std::string d_date) const;
    Day get_day(int d_id) const;
    int add_day(const Day& day) const;
    int delete_day(int d_id) const;

 private:
    int id;
    std::string weekday;
    std::string date;

    SqlWrapper postgres;
};

#endif  // DATABASE_DAY_H

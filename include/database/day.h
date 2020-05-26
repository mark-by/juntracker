#ifndef DATABASE_DAY_H
#define DATABASE_DAY_H

#include <string>
#include <vector>

#include "lesson.h"

class Day {
 public:
    Day(SqlWrapper& postgres)
        : postgres(postgres) {}
    explicit Day(int _id, std::string& _weekday, std::string& _date)
        : _id(_id)
        , _weekday(_weekday)
        , _date(_date) {}

    std::string get_weekday(std::string d_date) const;
    Day get_day(int d_id) const;
    int add_day(const Day& day) const;
    int delete_day(int d_id) const;

    [[nodiscard]] int id() const { return _id; }
    [[nodiscard]] std::string weekday() const { return _weekday; }
    [[nodiscard]] std::string date() const { return _date; }

 private:
    int _id;
    std::string _weekday;
    std::string _date;

    SqlWrapper postgres;
};

#endif  // DATABASE_DAY_H

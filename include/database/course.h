#ifndef _COURSE_H_
#define _COURSE_H_

#include <string>
#include <utility>
#include <vector>

#include "teacher.h"
#include "student.h"

#include "sql_wrapper.h"

class Course {
 public:
    Course(SqlWrapper& postgres)
    : postgres(postgres) {}
    explicit Course(int id, std::string& name, int price, std::string& start_date, std::string& end_date)
        : id(id)
        , name(name)
        , price(price)
        , start_date(start_date)
        , end_date(end_date) {}

    [[nodiscard]] Teacher get_teacher(const std::string& course_name) const;
    [[nodiscard]] int get_price(const std::string& course_name) const;
    void set_price(int price, const std::string& course_name);
    std::vector<Student> get_student_list() const;

 private:
    int id;
    std::string name;
    int price;
    std::string start_date;
    std::string end_date;

    SqlWrapper postgres;
};

#endif  // _COURSE_H_
#ifndef INCLUDE_DATABASE_COURSE_H_
#define INCLUDE_DATABASE_COURSE_H_

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <sstream>

#include "teacher.h"
#include "student.h"

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
    int set_price(int price, const std::string& course_name);
    [[nodiscard]] std::vector<Student> get_student_list(const std::string& course_name) const;
    [[nodiscard]] std::vector<Course> get_courses_by_teacher(int t_id);

    [[nodiscard]] Course get_course(int c_id) const;
    [[nodiscard]] int add_course(const Course& course) const;
    [[nodiscard]] int delete_course(int c_id) const;

 private:
    int id;
    std::string name;
    int price;
    std::string start_date;
    std::string end_date;

    SqlWrapper postgres;
};

#endif  // INCLUDE_DATABASE_COURSE_H_
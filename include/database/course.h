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
    explicit Course(int _id, std::string& _name, int _price, std::string& _start_date, std::string& _end_date)
        : _id(_id)
        , _name(_name)
        , _price(_price)
        , _start_date(_start_date)
        , _end_date(_end_date) {}

    [[nodiscard]] Teacher get_teacher(const std::string& course_name) const;
    [[nodiscard]] int get_price(const std::string& course_name) const;
    int set_price(int price, const std::string& course_name);
    [[nodiscard]] std::vector<Student> get_student_list(const std::string& course_name) const;
    [[nodiscard]] std::vector<Course> get_courses_by_teacher(int t_id);

    [[nodiscard]] Course get_course(int c_id) const;
    [[nodiscard]] int add_course(const Course& course) const;
    [[nodiscard]] int delete_course(int c_id) const;

    [[nodiscard]] int id() const { return  _id; }
    [[nodiscard]] std::string name() const { return  _name; }
    [[nodiscard]] int price() const { return  _price; }
    [[nodiscard]] std::string start_date() const { return  _start_date; }
    [[nodiscard]] std::string end_date() const { return  _end_date; }

 private:
    int _id;
    std::string _name;
    int _price;
    std::string _start_date;
    std::string _end_date;

    SqlWrapper postgres;
};

#endif  // INCLUDE_DATABASE_COURSE_H_
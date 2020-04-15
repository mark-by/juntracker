#ifndef _COURSE_H_
#define _COURSE_H_

#include <string>
#include <vector>

#include "teacher.h"
#include "student.h"

class Course {
 public:
    explicit Course();

    Teacher& get_teacher() const;
    int get_price() const;
    void set_price(int price);
    std::vector<Student> get_student_list() const;

 private:
    int id;
    std::string name;
    int price;
    std::string start_date;
    std::string end_date;
    Teacher teacher;
};

#endif  // _COURSE_H_
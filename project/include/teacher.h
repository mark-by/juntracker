#ifndef _TEACHER_H_
#define _TEACHER_H_

#include <string>
#include <vector>

#include "person.h"

class Teacher : public Person {
 public:
    explicit Teacher();

    std::string get_name() const override;
    std::string get_surname() const override;
    std::vector<std::string> get_courses() const;

 private:
    int id;
    std::string name;
    std::string surname;
    int salary;
    std::vector<std::string> courses;
    std::string description;
};

#endif  // _TEACHER_H_
#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <string>
#include <vector>

#include "person.h"

class Student : public Person {
 public:
    explicit Student();

    std::string get_name() const override;
    std::string get_surname() const override;

    std::vector<std::string> get_courses() const;
    void add_course(std::string course);

 private:
    int id;
    std::string name;
    std::string surname;
    int age;
    std::vector<std::string> courses;
    std::string description;
};

#endif  // STUDENT_H_
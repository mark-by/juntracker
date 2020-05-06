#ifndef _TEACHER_H_
#define _TEACHER_H_

#include <string>
#include <vector>

#include "person.h"
#include "sql_wrapper.h"

class Teacher : public Person {
 public:
    explicit Teacher(int id, std::string& name, std::string& surname, int salary, std::string& description)
        : id(id)
        , name(name)
        , surname(surname)
        , salary(salary)
        , description(description) {}

    std::string get_name(int t_id) const override;
    std::string get_surname(int t_id) const override;
    std::vector<std::string> get_courses() const;
    [[nodiscard]] std::string return_surname() const { return surname; }

 private:
    int id;
    std::string name;
    std::string surname;
    int salary;
//    std::vector<std::string> courses;
    std::string description;

    SqlWrapper postgres;
};

#endif  // _TEACHER_H_
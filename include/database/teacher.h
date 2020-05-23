#ifndef INCLUDE_DATABASE_TEACHER_H_
#define INCLUDE_DATABASE_TEACHER_H_

#include <string>
#include <vector>
#include <iostream>

#include "person.h"

class Teacher : public Person {
 public:
    Teacher(SqlWrapper& postgres)
    : postgres(postgres) {}
    explicit Teacher(int id, std::string& name, std::string& surname, int salary, std::string& description)
        : id(id)
        , name(name)
        , surname(surname)
        , salary(salary)
        , description(description) {}

    std::string get_name(int t_id) const override;
    std::string get_surname(int t_id) const override;

    [[nodiscard]] Teacher get_teacher(int t_id) const;
    [[nodiscard]] int add_teacher(const Teacher& teacher) const;
    [[nodiscard]] int delete_teacher(int t_id) const;

    [[nodiscard]] std::string return_surname() const { return surname; }

 private:
    int id;
    std::string name;
    std::string surname;
    int salary;
    std::string description;

    SqlWrapper postgres;
};

#endif  // INCLUDE_DATABASE_TEACHER_H_
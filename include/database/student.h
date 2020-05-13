#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "person.h"
#include "sql_wrapper.h"

class Student : public Person {
 public:
    Student(SqlWrapper& postgres)
    : postgres(postgres) {}
    explicit Student(int id, std::string& name, std::string& surname, int age, std::string& description)
        : id(id)
        , name(name)
        , surname(surname)
        , age(age)
        , description(description) {}

    [[nodiscard]] std::string get_name(int s_id) const override;
    [[nodiscard]] std::string get_surname(int s_id) const override;
    [[nodiscard]] int get_age(int s_id) const;

    [[nodiscard]] std::string get_course(int s_id) const;

    [[nodiscard]] Student get_student(int s_id) const;
    [[nodiscard]] int add_student(const Student& student) const;
    [[nodiscard]] int delete_student(int s_id) const;

    [[nodiscard]] std::string return_surname() const { return surname; }

 private:
    int id;
    std::string name;
    std::string surname;
    int age;
//    std::vector<std::string> courses;
    std::string description;

    SqlWrapper postgres;
};

#endif  // STUDENT_H_
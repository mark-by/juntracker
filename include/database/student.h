#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <string>
#include <vector>

#include "person.h"
#include "sql_wrapper.h"

class Student : public Person {
 public:
    explicit Student(int id, std::string& name, std::string& surname, int age, std::string& description)
        : id(id)
        , name(name)
        , surname(surname)
        , age(age)
        , description(description) {}

    std::string get_name(int s_id) const override;
    std::string get_surname(int s_id) const override;

    std::vector<std::string> get_courses() const;
    void add_course(std::string course);

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
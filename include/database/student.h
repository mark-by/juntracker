#ifndef INCLUDE_DATABASE_STUDENT_H_
#define INCLUDE_DATABASE_STUDENT_H_

#include "person.h"
class Student;
#include "course.h"

class Student : public Person {
 public:
    Student(SqlWrapper& postgres)
    : postgres(postgres) {}
    explicit Student(int _id, std::string& _name, std::string& _surname, int _age, SqlWrapper postgres)
        : _id(_id)
        , _name(_name)
        , _surname(_surname)
        , _age(_age)
        , postgres(postgres){}

    [[nodiscard]] int get_age(int s_id) const;
    std::vector<Course> get_courses() const;

    [[nodiscard]] Student get_student(int s_id) const;
    [[nodiscard]] int add_student(const Student& student) const;
    [[nodiscard]] int delete_student(int s_id) const;

    [[nodiscard]] int id() const override { return _id; }
    [[nodiscard]] std::string name() const override { return _name; }
    [[nodiscard]] std::string surname() const override { return _surname; }
    [[nodiscard]] int age() const { return _age; }

 private:
    int _id;
    std::string _name;
    std::string _surname;
    int _age;

    SqlWrapper postgres;
};

#endif  // INCLUDE_DATABASE_STUDENT_H_
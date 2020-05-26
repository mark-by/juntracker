#ifndef INCLUDE_DATABASE_TEACHER_H_
#define INCLUDE_DATABASE_TEACHER_H_

#include "person.h"
class Teacher;
#include "course.h"

class Teacher : public Person {
 public:
    Teacher(SqlWrapper& postgres)
    : postgres(postgres) {}
    explicit Teacher(int _id, std::string& _name, std::string& _surname, int _salary, std::string& _description, SqlWrapper postgres)
        : _id(_id)
        , _name(_name)
        , _surname(_surname)
        , _salary(_salary)
        , _description(_description)
        , postgres(postgres) {}

    std::vector<Course> get_courses() const;

    [[nodiscard]] Teacher get_teacher(int t_id) const;
    [[nodiscard]] int add_teacher(const Teacher& teacher) const;
    [[nodiscard]] int delete_teacher(int t_id) const;

    [[nodiscard]] int id() const override { return _id; }
    [[nodiscard]] std::string name() const override { return _name; }
    [[nodiscard]] std::string surname() const override { return _surname; }
    [[nodiscard]] int salary() const { return _salary; }
    [[nodiscard]] std::string description() const { return _description; }

 private:
    int _id;
    std::string _name;
    std::string _surname;
    int _salary;
    std::string _description;

    SqlWrapper postgres;
};

#endif  // INCLUDE_DATABASE_TEACHER_H_
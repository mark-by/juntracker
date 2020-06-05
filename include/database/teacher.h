#ifndef INCLUDE_DATABASE_TEACHER_H_
#define INCLUDE_DATABASE_TEACHER_H_

#include "person.h"

class Teacher;

#include "course.h"

class Teacher : public Person {
public:
    explicit Teacher(
            int _id,
            const std::string &_name,
            const std::string &_surname,
            int age,
            int _salary,
            const std::string &_tel_number,
            const std::string &_description)
            : _id(_id),
            _name(_name),
            _surname(_surname),
            _age(age),
            _tel_number(_tel_number),
            _salary(_salary),
            _description(_description) {}

    std::vector<Course> get_courses() const;
    int setMark(int lesson_id, int student_id, int mark, int school_id) const;

    static Teacher get_teacher(int teacher_id);
    static int save(const std::string& name, const std::string& surname, int school_id);
    static int update(int teacher_id, const std::string& name, const std::string& surname);
    static int remove(int teacher_id);

    int id() const override { return _id; }
    std::string name() const override { return _name; }
    std::string surname() const override { return _surname; }
    int salary() const { return _salary; }
    std::string description() const { return _description; }

private:
    int _id;
    std::string _name;
    std::string _surname;
    int _age;
    std::string _tel_number;
    int _salary;
    std::string _description;
};

#endif  // INCLUDE_DATABASE_TEACHER_H_
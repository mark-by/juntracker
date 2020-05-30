#ifndef INCLUDE_DATABASE_TEACHER_H_
#define INCLUDE_DATABASE_TEACHER_H_

#include "person.h"

class Teacher;

#include "course.h"

class Teacher : public Person {
public:
    explicit Teacher(int _id,
            const std::string &_name,
            int age,
            const std::string &_surname,
            int _salary,
            const std::string &_tel_number,
            const std::string &_description,
            const std::string &avatar)
            : _id(_id),
            _name(_name),
            _surname(_surname),
            _age(age),
            _tel_number(_tel_number),
            _salary(_salary),
            _description(_description),
            _avatar(avatar) {}

    std::vector<Course> get_courses() const;

    static Teacher get_teacher(int teacher_id);
    static int save(const std::string &name, const std::string &surname, int salary,
            int age, const std::string& tel_number, int user_id, const std::string& description);
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
    int _salary;
    std::string _tel_number;
    std::string _description;
    std::string _avatar;
};

#endif  // INCLUDE_DATABASE_TEACHER_H_
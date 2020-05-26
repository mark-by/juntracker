#ifndef INCLUDE_DATABASE_TEACHER_H_
#define INCLUDE_DATABASE_TEACHER_H_

#include "person.h"
class Teacher;
#include "course.h"

class Teacher : public Person {
 public:
    Teacher(SqlWrapper& postgres)
    : postgres(postgres) {}
    explicit Teacher(int _id, std::string& _name, std::string& _surname, int _salary, SqlWrapper postgres)
        : _id(_id)
        , _name(_name)
        , _surname(_surname)
        , _salary(_salary)
        , _description("")
        , postgres(postgres) {}

    std::vector<Course> get_courses() const;

    static Teacher get_teacher(int teacher_id);
    static int save(const std::string& name, const std::string& surname, int salary);
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
    int _salary;
    std::string _description;

    SqlWrapper postgres;
};

#endif  // INCLUDE_DATABASE_TEACHER_H_
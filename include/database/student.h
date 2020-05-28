#ifndef INCLUDE_DATABASE_STUDENT_H_
#define INCLUDE_DATABASE_STUDENT_H_

#include "person.h"
class Student;
#include "course.h"
#include "visit.h"
#include <boost/date_time/posix_time/posix_time.hpp>

class Student : public Person {
 public:
    explicit Student(int _id, std::string& _name, std::string& _surname, int _age)
        : _id(_id)
        , _name(_name)
        , _surname(_surname)
        , _age(_age)
        , _description("") {}

    std::vector<Course> get_courses() const;
    Visit get_visit(int lesson_id, const boost::posix_time::ptime & date) const;

    static Student get_student(int student_id);
    static int save(const std::string name, const std::string& surname, int age);
    static int remove(int student_id);

    int id() const override { return _id; }
    std::string name() const override { return _name; }
    std::string surname() const override { return _surname; }
    int age() const { return _age; }
    std::string description() const { return _description; }

 private:
    int _id;
    std::string _name;
    std::string _surname;
    int _age;
    std::string _description;
};

#endif  // INCLUDE_DATABASE_STUDENT_H_

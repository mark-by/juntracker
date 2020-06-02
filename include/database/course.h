#ifndef INCLUDE_DATABASE_COURSE_H_
#define INCLUDE_DATABASE_COURSE_H_

class Course;
#include "teacher.h"
#include "student.h"

class Course {
public:
    explicit Course(int _id, const std::string& _name, int _price, int teacher_id, int school_id):
        _id(_id), _name(_name), _price(_price), _school_id(school_id) { }

    static int set_price(int price, int course_id);
    std::vector<Student> get_students() const;

    static Course get_course(int course_id);
    static int save(const std::string& name, int price, int schoolId);
    static int remove(int course_id);

    int id() const { return  _id; }
    std::string title() const { return  _name; }
    int price() const { return  _price; }

 private:
    int _id;
    std::string _name;
    int _price;
    int _school_id;
};

#endif  // INCLUDE_DATABASE_COURSE_H_
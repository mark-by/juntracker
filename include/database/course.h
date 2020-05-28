#ifndef INCLUDE_DATABASE_COURSE_H_
#define INCLUDE_DATABASE_COURSE_H_

class Course;
#include "teacher.h"
#include "student.h"

class Course {
 public:
    explicit Course(int _id, std::string& _name, int _price)
        : _id(_id)
        , _name(_name)
        , _price(_price){}
    explicit Course(std::string& _name, int _price)
        : _name(_name)
        , _price(_price) {}

    Teacher get_teacher() const;
    static int set_price(int price, int course_id);
    std::vector<Student> get_students() const;

    static Course get_course(int course_id);
    static int save(const std::string& name, int price);
    static int remove(int course_id);

    int id() const { return  _id; }
    std::string name() const { return  _name; }
    int price() const { return  _price; }

 private:
    int _id;
    std::string _name;
    int _price;

    SqlWrapper db;
};

#endif  // INCLUDE_DATABASE_COURSE_H_
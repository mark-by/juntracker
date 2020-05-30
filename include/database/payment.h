#ifndef INCLUDE_DATABASE_PAYMENT_H_
#define INCLUDE_DATABASE_PAYMENT_H_

#include "sql_wrapper.h"
#include "course.h"

class Payment {
 public:
    explicit Payment(int _id, int _student_id, int _course_id, int _amount, std::string& _payment_date, int _school_id)
            : _id(_id),
              _student_id(_student_id),
              _course_id(_course_id),
              _amount(_amount),
              _payment_date(_payment_date),
              _school_id(_school_id) {}
    
    Student get_student() const;
    Course get_course() const;


    static Payment get_payment(int payment_id);
    static int save(int student_id, int course_id, int amount, std::string& payment_date, int school_id);
    static int remove(int payment_id);

    int id() const { return _id; }
    int amount() const { return _amount; }
    std::string payment_date() const { return _payment_date; }

 private:
    int _id;
    int _student_id;
    int _course_id;
    int _amount;
    std::string _payment_date;
    int _school_id;
};

#endif  // INCLUDE_DATABASE_PAYMENT_H_
#ifndef _PAYMENT_H_
#define _PAYMENT_H_

#include <string>
#include <iostream>

#include "sql_wrapper.h"

class Payment {
 public:
    Payment(SqlWrapper& postgres)
    : postgres(postgres) {}
    explicit Payment(int id, int student_id, int course_id, std::string& payment_date)
            : id(id)
            , student_id(student_id)
            , course_id(course_id)
            , payment_date(payment_date) {}
    
    int get_student_id(int p_id) const;
    int get_course_id(int p_id) const;

    void add_payment(int pid, int s_id, int c_id, int amount, const std::string& date);

 private:
    int id;
    int student_id;
    int course_id;
    int amount;
    std::string payment_date;

    SqlWrapper postgres;
};

#endif  // _PAYMENT_H_